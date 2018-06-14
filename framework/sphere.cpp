#include "sphere.hpp"
#include <iostream>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>



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

//Sphere::~Sphere() {}
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

bool Sphere::intersect (Ray const& ray, float distance) const
{
    glm::vec3 ray_origin = ray.origin; 
    glm::vec3 ray_direction = ray.direction; 

    return glm::intersectRaySphere (ray_origin, ray_direction, center_ , radius_ * radius_ , distance);     
}
//Diese Methode gibt einen bool zurück, ob der Ray der übergeben wird das Objekt von Sphere trifft. 
//Dafür braucht die Methode zusätzlich noch die Distanz, die übergeben wird und nimmt sich die Attribute aus der Sphere Klasse 
