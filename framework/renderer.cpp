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
#include "hit.hpp"

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
  Color backgroundColor{0,0.8,0.4};   
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
    Color pix_col = shade(*closest_object, ray, closest_hit, *scene.light_vector[0],  backgroundColor, scene.camera);
    return pix_col;
  }
 
    return backgroundColor;

}


Color Renderer::shade (Shape const& shape, Ray const& ray, std::shared_ptr<Hit> hit, Light const& light, Color const& ambient, Camera const& camera) 
{
  //Diffuses Licht
  glm::vec3 intersect = hit->position; 
  glm::vec3 lightvector = glm::normalize(light.position_-intersect); 
  glm::vec3 normalvector = hit->normal;
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