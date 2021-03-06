#include "sphere.hpp"
#include <iostream>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "hit.hpp"
#include <glm/gtx/intersect.hpp>
 

Sphere::Sphere(): 
    Shape(),
    center_{0.0f, 0.0f, 0.0f},
    radius_{0.5f}
    {}


Sphere::Sphere(glm::vec3 const& center, float radius):
    Shape(),
    center_{center},
    radius_{radius}
    {}

//Aufgabe 6.4 
Sphere::Sphere(std::shared_ptr<Material> const& material, std::string const& name, glm::vec3 const& center, float radius): 
    Shape(material, name), //einzige Möglichkeit um auf die Membervariablen der Basisklasse zuzugreifen
    center_{center},
    radius_{radius}
    {}

Sphere::~Sphere() 
    {}
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

std::shared_ptr<Hit> Sphere::intersect (Ray const& ray) const
{ 
    glm::vec3 position; 
    glm::vec3 normal; 
    glm::vec3 ray_direction = glm::normalize(ray.direction);   

    bool result = glm::intersectRaySphere (ray.origin, ray_direction, center_ , radius_ , position, normal); 
    if (result) {
        std::shared_ptr<Hit> t = std::make_shared<Hit> (Hit{position, normal});
        return t;
        //hier wird ein shared:ptr auf Hit angelegt, der position und normal bekommt
        }
    return nullptr; 
}
//Diese Methode gibt einen Shared:ptr auf einen Hit zurück, ob der Ray der übergeben wird das Objekt von Sphere trifft. 
//Dafür braucht die Methode zusätzlich noch die Distanz, die übergeben wird und nimmt sich die Attribute aus der Sphere Klasse 
