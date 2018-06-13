#include "sphere.hpp"
#include <iostream>
#include <cmath>

//Konstruktoren 

Sphere::Sphere(): 
Shape(),
center_{0.0f, 0.0f, 0.0f},
radius_{0.5f}
{}

Sphere::Sphere(Color const& color, std::string const& name, glm::vec3 const& center, float radius): 
Shape(color, name), //einzige Möglichkeit um auf die Membervariablen der Basisklasse zuzugreifen
center_{center},
radius_{radius}
{}

Sphere::~Sphere() {}
//Destruktoren legt man nur an wenn sie Sekundärressourcen freigeben müssen 


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