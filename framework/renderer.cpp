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
}

void Renderer::tone_mapping(Color& current_color)
{
  float r_ = current_color.r / (current_color.r +1);
  float g_ = current_color.g / (current_color.g +1); 
  float b_ = current_color.b / (current_color.b +1); 
  current_color = Color {r_, g_, b_}; 
}

void Renderer::render(Scene const& scene)
{
   for(int i = 0; i < 2; ++i){
    
    scene.light_vector.at(0)->position_ = glm::vec3{-80, 200, 100 - i };
    //send a ray through each pixel
    for (unsigned y=0; y < height_; ++y) 
    {
      for (unsigned x=0; x < width_; ++x) 
      {
        Pixel p (x,y);           
        Ray ray = scene.camera.shoot_ray(x,y, width_, height_); 
        //cout<<scene.shape_vector.size()<<endl;
        Color color{0.0, 0.0, 0.0};
        color = trace(scene,ray); 
        //tone_mapping(color); 
        p.color = color; 
        write(p);
      }
    }
    ppm_.save(filename_+ "_" + std::to_string(i) + ".ppm");
  }
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
    
    Ray light_ray{hit->position + 0.1f* hit->normal, lightvector}; //Prüfen, ob zwischen dem Schnittpunkt&Licht ein Objekt liegt
    for(std::shared_ptr<Shape> const& shape : scene.shape_vector)
    {
      if(shape->intersect(light_ray) != nullptr)
      {
        can_see_light = false;
        break;
      }
    }
    
    if (can_see_light)
    {
      float kreuzprodukt1 = glm::dot(hit->normal,lightvector);
      diffuseLight = (shape.m_->kd) * light->get_intensity(light->color_, light->brightness_) * kreuzprodukt1; 
      light_colors.push_back(diffuseLight);
    }
  }

  for (int i = 0; i < light_colors.size(); ++i)
  {
    Color clr = light_colors.at(i); 
    diffuseLight += clr;
  }
  diffuseLight.bound_check();
  return diffuseLight;  
}



Color Renderer::calculate_specular(Shape const& shape,std::shared_ptr<Hit> const& hit, Scene const& scene) const
{
  Color specularLight{0.0,0.0,0.0};
  std::vector<Color> light_colors{}; 
 
  for (std::shared_ptr<Light> light : scene.light_vector) 
  {
    bool can_see_light = true; 
    glm::vec3 lightvector = glm::normalize(light->position_ - hit->position); 

    Ray light_ray{hit->position + 0.1f* hit->normal, lightvector}; //Schatten
    for(std::shared_ptr<Shape> const& shape : scene.shape_vector)
    {
      if(shape->intersect(light_ray) != nullptr)
      {
        can_see_light = false;
        break;
      }
    }

    if (can_see_light)
    {
      float m_exp = shape.m_->m_exponent;
      glm::vec3 cameravector = glm::normalize(scene.camera.position_ - hit->position); 
      glm::vec3 reflectvector = glm::dot(hit->normal, lightvector) * 2.0f * hit->normal - lightvector; 
      float kreuzprodukt2 = glm::dot(cameravector, reflectvector);
      if (kreuzprodukt2 < 0)
            kreuzprodukt2 = -kreuzprodukt2; 
      float cosinus = pow(kreuzprodukt2, m_exp);
      float m_phi = (m_exp + 2)/(2* M_PI);
      Color specularLight = (shape.m_->ks) * light->get_intensity(light->color_, light->brightness_) * m_phi * cosinus;
      light_colors.push_back(specularLight); 
    } 
  }

  for (int i=0; i<light_colors.size(); ++i)
  {
   Color clr = light_colors.at(i); 
   specularLight += clr; 
  } 
specularLight.bound_check(); 
return specularLight; 
}


Color Renderer::shade (Shape const& shape, Ray const& ray, std::shared_ptr<Hit> hit, Scene const& scene) 
{
  Color ambientlight =  shape.m_->ka * scene.ambient;
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