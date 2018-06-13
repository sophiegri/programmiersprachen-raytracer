#include "sphere.hpp"
#include <iostream>
#include <cmath>

//Konstruktoren 

Sphere::Sphere(): 
Shape(),
center_{0.0f, 0.0f, 0.0f},
radius_{0.5f}
{}

Sphere::Sphere(float radius):
radius_{radius}
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
    return 4*M_PI * pow(get_radius(), 2);
} 


float Sphere::volume() const
{
    return (4.0f/3.0f)* M_PI * pow(get_radius(), 3);
}



std::ostream& operator<< (std::ostream& os, const Sphere& s)
{
    return s.print(os);
}

std::ostream& Sphere::print (std::ostream& os) const
{
    Shape::print(os);
    os
     << "Position: " << center_.x << "," << center_.y <<  center_.z << "\n"     
     << "Radius: " << radius_<< "\n"; 
    return os;
}