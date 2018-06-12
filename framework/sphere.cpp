#include "sphere.hpp"
#include <iostream>
#include <cmath>

//Konstruktoren 

Sphere::Sphere(): 
center_{0.0f, 0.0f, 0.0f},
radius_{0.5f}
{}

Sphere::Sphere(glm::vec3 const& center, float const& radius):
center_{center},
radius_{radius}
{}

Sphere::~Sphere() {}

//Methoden 

glm::vec3 Sphere::get_center() const
{
    return center_; 
} 

float Sphere::get_radius() const
{
    return radius_; 
}

float Sphere::area() const
{
    return 4*M_PI *pow(get_radius(), 2);
} 


float Sphere::volume() const
{
    return (4/3)* M_PI * (pow(get_radius(), 3));
}