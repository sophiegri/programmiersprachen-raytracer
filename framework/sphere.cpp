#include "sphere.hpp"

//Konstruktoren 

Sphere::Sphere(): 
center_{0},
radius_{0.0f}
{}

Sphere::Sphere(glm::vec3 const& center, float const& radius):
center_{center},
radius_{radius}
{}

//Methoden 

glm::vec3 const& get_center() const
{
    return center_; 
} 

float const& get_radius() const
{
    return radius_; 
}

float area() const override
{
//not implemented yet 
} 


float volume() const override
{
//not implemented yet 
}