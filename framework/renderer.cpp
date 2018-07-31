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

Color Renderer::shade (Shape const& shape, Ray const& ray, float t, Light const& light) 
{
  glm::vec3 intersect = ray.direction - ray.direction*t; 
  glm::vec3 lightvector = glm::normalize(light.position_-intersect); 
  glm::vec3 normalvector = glm::normalize(shape.get_normal(intersect)); 

  Color dieseserste =  light.intensity_  * (shape.m_->kd) * glm::dot(normalvector,lightvector); 
  return dieseserste; 
  //glm::dot berechnet das Kreuzprodukt zweier Vektoren 
}

void Renderer::render(Scene const& scene)
{
  
  Color blue (0.1f, 0.5f, 0.6f);
  Color pink (0.6f,0.2f,0.4f); 

  for (unsigned y=0; y < height_; ++y) 
  {
    for (unsigned x=0; x < width_; ++x) 
    {
      Pixel p (x,y); 

      //send a ray through each pixel
      Ray ray {glm::vec3{x, y, 0.0f}, glm::vec3{0.0f, 0.0f, -1.0f}};
      float t = 2000.0f; 

      //check for intersections
      if ((*scene.shape_vector[0]).intersect(ray, t) == true)
      {
        //Color the pixel 
        //p.color = blue; 
        p.color = shade(*scene.shape_vector[0],ray,t, *scene.light_vector[0]);

      }
      else 
      {
        p.color = pink; 
      }
      write(p);
    }
  }
  ppm_.save(filename_);
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

