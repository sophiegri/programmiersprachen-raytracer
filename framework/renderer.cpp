// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <algorithm>


Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}



void Renderer::render()
{
  std::size_t const checker_pattern_size = 50;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color(0.0, 0.8, float(x)/height_);
      } else {
        p.color = Color(0.3, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}


//Die get_intensity ist schon im light definiert 
/* Color Renderer::get_intensity (Color const& color, unsigned int brightness)const
{
  Color i (color.r*brightness, color.g*brightness, color.b*brightness);
  return i; 
}  */



void Renderer::render(Scene const& scene)
{
  //send a ray through each pixel
  for (unsigned y=0; y < height_; ++y) 
  {
    for (unsigned x=0; x < width_; ++x) 
    {
      Pixel p (x,y);           
      Ray ray = scene.camera.shoot_ray(x,y, width_, height_); 
      //cout<<scene.shape_vector.size()<<endl;
      p.color = trace(scene,ray);
      write(p);
    }
  }
  ppm_.save(filename_);
}

Color Renderer::trace (Scene const& scene, Ray const& ray)
{
  Color backgroundColor{0.2, 0.2, 0.2};   
  std::shared_ptr<Hit> hit = nullptr; 
  std::shared_ptr<Hit> closest_hit = nullptr; 
  std::shared_ptr<Shape> closest_object{nullptr};
  float closest_distance = 1000000;

  for (auto const& i : scene.shape_vector)
  {
    hit = (*i).intersect(ray);
   
    if (hit != nullptr)
    {
      
      if (glm::length(hit->position-ray.origin) < closest_distance)
      {
        closest_hit = hit;
        closest_distance = glm::length(hit->position-ray.origin);
        closest_object = i;
      }
    }
  }
  
  if (closest_object != nullptr)
  {
    Color pix_col = shade(*closest_object, ray, closest_hit, scene);
    return pix_col;
  }
 
    return backgroundColor;

}

Color Renderer::calculate_diffuse(Shape const& shape, std::shared_ptr<Hit> hit, Scene const& scene)const
{
  Color diffuseLight{0.0,0.0,0.0};
  std::vector<Color> light_colors{}; 
 
  for (std::shared_ptr<Light> light : scene.light_vector) 
  {
    bool can_see_light = true; 
    glm::vec3 lightvector = glm::normalize(light->position_ - hit->position); 
    
    Ray light_ray{hit->position + 0.1f* hit->normal, lightvector};
    for(std::shared_ptr<Shape> const& shape : scene.shape_vector){
      if(shape->intersect(light_ray) != nullptr){
        can_see_light = false;
        break;
      }
    }
    //Hier sollte noch eingebaut werden, wenn der Schnittpunkt im Objekt ist 
    if (can_see_light)
    {
      float kreuzprodukt1 = std::max(glm::dot(hit->normal,lightvector),(float)0);
      diffuseLight = (shape.m_->kd) * light->get_intensity(light->color_, light->brightness_) * kreuzprodukt1; 
      light_colors.push_back(diffuseLight);
    }
  }

  for (int i = 0; i < light_colors.size(); ++i)
  {
    Color clr = light_colors.at(i); 
    diffuseLight += clr; 
  }
  return diffuseLight;  
}



Color Renderer::calculate_specular(Shape const& shape,std::shared_ptr<Hit> const& hit, Scene const& scene)const
{
  Color specularLight{0.0,0.0,0.0};
  std::vector<Color> light_colors{}; 
 
  for (std::shared_ptr<Light> light : scene.light_vector) 
  {
    bool can_see_light = true; 
    glm::vec3 lightvector = glm::normalize(light->position_ - hit->position); 
    
    //Hier sollte noch eingebaut werden, wenn der Schnittpunkt im Objekt ist 
    if (can_see_light)
    {
      glm::vec3 cameravector = glm::normalize(scene.camera.position_ - hit->position); 
      glm::vec3 reflectvector = glm::normalize((2* glm::dot(hit->normal, lightvector)*hit->normal)-lightvector); 
      float kreuzprodukt2 = std::max(glm::dot(cameravector, reflectvector), (float)0);

      if (kreuzprodukt2 < 0)
            kreuzprodukt2 = -kreuzprodukt2; 

      Color specularLight = (shape.m_->ks) * light->get_intensity(light->color_, light->brightness_) * pow(kreuzprodukt2,shape.m_->m_exponent);
      light_colors.push_back(specularLight); 
    } 
  }

  for (int i=0; i<light_colors.size(); ++i)
  {
   Color clr = light_colors.at(i); 
   specularLight += clr; 
  } 

return specularLight; 
}


Color Renderer::shade (Shape const& shape, Ray const& ray, std::shared_ptr<Hit> hit, Scene const& scene) 
{
  Color ambientlight = scene.ambient * shape.m_->ka;
  return calculate_diffuse(shape,hit,scene) + ambientlight + calculate_specular(shape,hit,scene); 
}



void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}