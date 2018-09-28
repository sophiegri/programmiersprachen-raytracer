// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color(float red, float green, float blue) : r(red), g(green), b(blue) {}

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  void bound_check() {
	  if (r > 1) {
		  r = 1;
	  } else if (r < 0) {
		  r = 0;
	  }
	  if (g > 1) {
		  g = 1;
	  }
	  else if (g < 0) {
		  g = 0;
	  }
	  if (b > 1) {
		  b = 1;
	  }
	  else if (b < 0) {
		  b = 0;
	  }
}

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    bound_check();
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    bound_check();
    return *this;
  }

  Color& operator*=(Color const& other)
  {
    r *= other.r; 
    g *= other.g; 
    b *= other.b;
    bound_check(); 
    return *this; 
  }

  Color& operator*=(float b)
  {
    r *= b; 
    g *= g; 
    b *= b; 
    bound_check();
    return *this; 
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(Color const& a, Color const& b)
  {
    auto tmp(a); 
    tmp *= b; 
    return tmp; 
  }

  friend Color operator*(Color const& a, float b)
  {
    auto tmp(a); 
    tmp.r = a.r*b; 
    tmp.g = a.g*b; 
    tmp.b = a.b*b; 
    tmp.bound_check();
    return tmp; 
  }  

  float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
