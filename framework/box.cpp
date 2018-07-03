#include "box.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp> 
#include <iostream>
#include <limits> // numeric_limits 
#include <math.h> // isinf
using namespace std;

//Konstruktoren 

Box::Box(): 
Shape(),
min_{0.0f, 0.0f, 0.0f},
max_{1.0f, 1.0f, 1.0f}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
Shape(),
min_{min},
max_{max}
{}

Box::Box(Color const& color, std::string const& name, glm::vec3 const& min, glm::vec3 const& max):
Shape(color, name),
min_{min},
max_{max}
{}

//Box::~Box() {}


glm::vec3 Box::get_min() const 
{
    return min_; 
}

glm::vec3 Box::get_max() const 
{
    return max_; 
}

float Box::area() const
{
    float length = max_.x - min_.x; 
    float heigth = max_.y - min_.y; 
    float width = max_.z - min_.z; 
    return 2*(length*heigth)+ 2*(length*width) + 2*(heigth*width);
}

float Box::volume() const
{
    float length = max_.x - min_.x; 
    float heigth = max_.y - min_.y; 
    float width = max_.z - min_.z; 
    return length * heigth * width;     
}


std::ostream& operator<< (std::ostream& os, const Box& b)
{
    return b.print(os);
}


 std::ostream& Box::print (std::ostream& os) const
 {
     Shape::print(os);
     os
     << "Position_Minimum: " << min_.x << "," << min_.y <<  min_.z << "\n"
     << "Position_Maximum: " << max_.x << "," << max_.y <<  max_.z << "\n";
     return os;
 }

 //Aufgabe 6.3 
 bool Box::intersect(Ray const& ray, float& t) const
 {
     if (ray.direction.x != 0)
     //Hier wird ausgeschlossen, dass später durch 0 geteilt wird 
     {
         if (ray.direction.x > 0)
         {
             float t_x = (min_.x - ray.origin.x) / ray.direction.x;
            //Berechnung des t von der x-min Seite

            if (t_x>0)
            {
                glm::vec3 intersection_point = ray.origin + t_x * ray.direction;
                //Schnittpunkt Berechnung für die Seite x-Min

                if ((intersection_point.y <= max_.y 
                && intersection_point.y >= min_.y) 
                && (intersection_point.z <= max_.z 
                && intersection_point.z >= min_.z))
                //Überprüfung ob der Schnittpunkt innerhalb der Box ist
                {
                    std::cout << "Schnittpunkt_x: " <<intersection_point.x << endl;
                    std::cout << "Schnittpunkt_y: " <<intersection_point.y << endl;
                    std::cout << "Schnittpunkt_z: " <<intersection_point.z << endl;
                    return true;
                }
            }  
         }
     }

    if (ray.direction.y != 0) 
    {
        if (ray.direction.y > 0)
        {
            float t_y = (min_.y - ray.origin.y) / ray.direction.y;
            //Berechnung des t von der y-min Seite
            if (t_y>0)
            {
                glm::vec3 intersection_point = ray.origin + t_y * ray.direction;
                //Schnittpunkt Berechnung für die Seite y-Min
                if ((intersection_point.x <= max_.x 
                    && intersection_point.x >= min_.x) 
                    && (intersection_point.z <= max_.z 
                    && intersection_point.z >= min_.z))
                //Überprüfung ob der Schnittpunkt innerhalb der Box ist
                {  
                return true;
                }
            }  
        }
    }

    if (ray.direction.z != 0) 
    {
        if (ray.direction.z > 0)
        {
            float t_z = (min_.z - ray.origin.z) / ray.direction.z;
            //Berechnung des t von der z-min Seite
            if (t_z>0)
            {
                glm::vec3 intersection_point = ray.origin + t_z * ray.direction;
                //Schnittpunkt Berechnung für die Seite z-Min
                if ((intersection_point.x <= max_.x 
                    && intersection_point.x >= min_.x) 
                    && (intersection_point.y <= max_.y 
                    && intersection_point.y >= min_.y))
                //Überprüfung ob der Schnittpunkt innerhalb der Box ist
                {  
                return true;
                }
            }  
        }
    }
 }

 /*      float t_x = (min_.x - ray.origin.x) / ray.direction.x;
     //Berechnung des t von der x-min Seite

      if (isinf(t_x))
     //inf wird zurückgegeben wenn durch 0 geteilt wird, in diesem Fall 
     //ist kein Schnittpunkt vorhanden 
     {
         std::cout << "Our intersection point does not exist." << endl; 
         return false;
     }  */


