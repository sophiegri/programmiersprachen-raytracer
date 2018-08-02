// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render();
  void render(Scene const& scene);
  Color shade (Shape const& shape, Ray const& ray, float t, Light const& light, Color const& ambient);
  void write(Pixel const& p);
  Color get_intensity (Color const& color, unsigned int brightness);


  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
