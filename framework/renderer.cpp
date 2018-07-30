// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

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

void Renderer::render(Ray const& ray, Shape const& shape)
{
  
  //Color pixel_col [height_][width_];
  Color blue (0.1f, 0.5f, 0.6f);
  Color pink (0.6f,0.2f,0.4f); 
  //Sphere sphere {red, rsphere, {0.0f, 0.0f, 5.0f}, 1.0f};

  for (unsigned y=0; y < height_; ++y) 
  {
    for (unsigned x=0; x < width_; ++x) 
    {
      Pixel p (x,y); 

      //send a ray through each pixel
      Ray ray {glm::vec3{x, y, 0.0f}, glm::vec3{0.0f, 0.0f, -1.0f}};

      float t = 2000.0f; 

      //check for intersections
      if (shape.intersect(ray, t) == true)
      {
        //Color the pixel 
        //pixel_col [y] [x] = white; 

        p.color = blue; 

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

