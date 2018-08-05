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



Color Renderer::get_intensity (Color const& color, unsigned int brightness)
{
  Color i (color.r*brightness, color.g*brightness, color.b*brightness);
  return i; 
} 



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
  Color blue (0.1f, 0.5f, 0.6f);
  //Scene scene; 
  Camera camera {"new camera", glm::vec3{0,0,0}, glm::vec3{0,0,0}, 45.0f};   
  float distance = 1000; 
  Sphere sphere (glm::vec3 {0,0,0}, 1.2f);

  //Das ist nur ein Test um zu schauen warum ich nichts sehe 
  float closest_distance = 100; 
  bool intersection = false; 
  float closest_object = -1; 

/*   bool intersection; 
  intersection = sphere.intersect(ray,distance); 
  if ((intersection == true) && (distance < closest_distance))
  {
    closest_distance = distance; 
    return blue; 
  }
  else 
  {
    return {0,0,0}; 
  } */
  for (int i=0; i< scene.shape_vector.size(); ++i)
  {
  intersection = (*scene.shape_vector[i]).intersect(ray, distance);
  //cout<<distance<<endl;
    if(intersection==true){
      cout<<"true"<<endl;
    }
    if((distance == closest_distance)){
      cout<<"true2"<<endl;
    }
    if ( (distance < closest_distance) && (intersection == true) )
    {
      cout<<"intersection"<<endl;
      closest_distance = distance; 
      closest_object = i; 
    }
  }
  if (closest_object != -1)
  {
    cout<<"nicht intersection"<<endl;
    Color pix_col = shade(*scene.shape_vector[closest_object], ray, distance, *scene.light_vector[0],  blue, camera);
    return pix_col;
  }
  else 
  {
    return Color{0,0,0}; 
  }
}


Color Renderer::shade (Shape const& shape, Ray const& ray, float t, Light const& light, Color const& ambient, Camera const& camera) 
{
  //Diffuses Licht
  glm::vec3 intersect = ray.origin + ray.direction*t; 
  glm::vec3 lightvector = glm::normalize(light.position_-intersect); 
  glm::vec3 normalvector = glm::normalize(shape.get_normal(intersect));
  float kreuzprodukt1 = std::max(glm::dot(normalvector,lightvector),(float)0);
  //glm::dot berechnet das Kreuzprodukt zweier Vektoren 
  Color diffuslight = (shape.m_->kd) * get_intensity(light.color_, light.brightness_) * kreuzprodukt1; 

  //Ambientes Licht
  Color ambientlight = ambient * (shape.m_->ka);
  
  //Reflexion Licht
  glm::vec3 cameravector = glm::normalize(camera.position_-intersect); 
  glm::vec3 reflectvector = glm::normalize((2* glm::dot(normalvector, lightvector)*normalvector)-lightvector); 
  float kreuzprodukt2 = std::max(glm::dot(cameravector, reflectvector), (float)0);
  Color reflectlight = (shape.m_->ks) * get_intensity(light.color_, light.brightness_) * pow(kreuzprodukt2,shape.m_->m_exponent);
  
  return diffuslight + ambientlight + reflectlight; 
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