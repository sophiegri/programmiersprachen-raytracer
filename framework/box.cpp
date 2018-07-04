#include "box.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp> 
#include <iostream>
#include <limits> // numeric_limits 
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

//Alter Konstruktor wegen der Tests
Box::Box(Color const& color, std::string const& name, glm::vec3 const& min, glm::vec3 const& max):
Shape(color, name),
min_{min},
max_{max}
{}

Box::Box(std::shared_ptr<Material> const& material, std::string const& name, glm::vec3 const& min, glm::vec3 const& max):
Shape(material, name),
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
     t = std::numeric_limits<float>::max();
     //hier steht nun in t der maximal größte float 
     bool intersection = false;

     //1. Schnittpunkt Test Seite X-min      
     if (ray.direction.x != 0)
     //Hier wird ausgeschlossen, dass später durch 0 geteilt wird 
     {
         if (ray.direction.x > 0)
         {
             float t_min_x = (min_.x - ray.origin.x) / ray.direction.x;
             //berechne meine Distanz zu x-min
             
             if (t_min_x > 0) 
             //sehe ich meinen Punkt überhaupt, weil größer als 0 
             {
                 glm::vec3 intersection_point_x_min = ray.origin + t_min_x * ray.direction;

                 if (  (intersection_point_x_min.y <= max_.y && intersection_point_x_min.y >= min_.y) 
                    && (intersection_point_x_min.z <= max_.z && intersection_point_x_min.z >= min_.z) )
                    //liegt mein Schnittpunkt innerhalb meiner Box? 
                    {
                         if (t_min_x < t)
                         //ist das t von x-min kleiner als mein ursprüngliches t 
                        {
                            t = t_min_x;
                            intersection = true; 
                            //setze t auf den kleineren t-wert und sage es gibt einen Schnittpunkt 
                        }
                    }               
                }
            }
        }

     //2. Schnittpunkt Test Seite X-max      
     if (ray.direction.x != 0)
     {
         if (ray.direction.x > 0)
         {
             float t_max_x = (max_.x - ray.origin.x) / ray.direction.x;
             
             if (t_max_x > 0)  
             {
                 glm::vec3 intersection_point_x_max = ray.origin + t_max_x * ray.direction;

                 if (  (intersection_point_x_max.y <= max_.y && intersection_point_x_max.y >= min_.y) 
                    && (intersection_point_x_max.z <= max_.z && intersection_point_x_max.z >= min_.z) )
                    {
                         if (t_max_x < t) 
                         {
                            t = t_max_x;
                            intersection = true;  
                         }
                    }               
                }
            }
        }

     //3. Schnittpunkt Test Seite Y-min      
     if (ray.direction.y != 0) 
     {
         if (ray.direction.y > 0)
         {
             float t_min_y = (min_.y - ray.origin.y) / ray.direction.y;
             
             if (t_min_y > 0)  
             {
                 glm::vec3 intersection_point_y_min = ray.origin + t_min_y * ray.direction;

                 if (  (intersection_point_y_min.x <= max_.x && intersection_point_y_min.x >= min_.x) 
                    && (intersection_point_y_min.z <= max_.z && intersection_point_y_min.z >= min_.z) )
                    {
                         if (t_min_y < t) 
                        {
                            t = t_min_y;
                            intersection = true; 
                        }
                    }               
                }
            }
        }

     //4. Schnittpunkt Test Seite Y-max      
     if (ray.direction.y != 0)
     {
         if (ray.direction.y > 0)
         {
             float t_max_y = (max_.y - ray.origin.y) / ray.direction.y;
             
             if (t_max_y > 0)  
             {
                 glm::vec3 intersection_point_y_max = ray.origin + t_max_y * ray.direction;

                 if (  (intersection_point_y_max.x <= max_.x && intersection_point_y_max.x >= min_.x) 
                    && (intersection_point_y_max.z <= max_.z && intersection_point_y_max.z >= min_.z) )
                    {
                         if (t_max_y < t) 
                         {
                            t = t_max_y;
                            intersection = true;  
                         }
                    }               
                }
            }
        }

     //5. Schnittpunkt Test Seite Z-min      
     if (ray.direction.z != 0) 
     {
         if (ray.direction.z > 0)
         {
             float t_min_z = (min_.z - ray.origin.z) / ray.direction.z;
             
             if (t_min_z > 0)  
             {
                 glm::vec3 intersection_point_z_min = ray.origin + t_min_z * ray.direction;

                 if (  (intersection_point_z_min.x <= max_.x && intersection_point_z_min.x >= min_.x) 
                    && (intersection_point_z_min.y <= max_.y && intersection_point_z_min.y >= min_.y) )
                    {
                         if (t_min_z < t) 
                        {
                            t = t_min_z;
                            intersection = true; 
                        }
                    }               
                }
            }
        }

     //6. Schnittpunkt Test Seite Z-max      
     if (ray.direction.z != 0)
     {
         if (ray.direction.z > 0)
         {
             float t_max_z = (max_.z - ray.origin.z) / ray.direction.z;
             
             if (t_max_z > 0)  
             {
                 glm::vec3 intersection_point_z_max = ray.origin + t_max_z * ray.direction;

                 if (  (intersection_point_z_max.x <= max_.x && intersection_point_z_max.x >= min_.x) 
                    && (intersection_point_z_max.y <= max_.y && intersection_point_z_max.y >= min_.y) )
                    {
                         if (t_max_z < t) 
                         {
                            t = t_max_z;
                            intersection = true;  
                         }
                    }               
                }
            }
        }
        return intersection;
    }


/* 






             float t_max_x = (max_.x - ray.origin.x) / ray.direction.x; 
            //Berechnung des t von der x-min / x-max Seite


            if (t_min_x > 0 || t_max_x > 0) 
            {
                glm::vec3 intersection_point_x_min = ray.origin + t_min_x * ray.direction;
                glm::vec3 intersection_point_x_max = ray.origin + t_max_x * ray.direction; 
                //Schnittpunkt Berechnung für die Seite x-Min

                if ( ( (intersection_point_x_min.y <= max_.y && intersection_point_x_min.y >= min_.y) 
                    && (intersection_point_x_min.z <= max_.z && intersection_point_x_min.z >= min_.z))
                    || ((intersection_point_x_max.y <= max_.y && intersection_point_x_max.y >= min_.y) 
                    && (intersection_point_x_max.z <= max_.z && intersection_point_x_max.z >= min_.z)
                   ) )
                {
                    intersection = true; 

                    if (t_min_x < t_max_x)
                    {
                        std::cout << "Schnittpunkt bei der Distanz (x-min): " << t_min_x << endl; 
                        t = t_min_x; 
                          
                    }
                    else 
                    {
                        std::cout << "Schnittpunkt bei der Distanz (x-max): " << t_max_x << endl;
                        t = t_max_x; 
                    }
                }
            } 
         }
     }

    if (ray.direction.y != 0) 
    {
        if (ray.direction.y > 0)
        {
            float t_min_y = (min_.y - ray.origin.y) / ray.direction.y;
            float t_max_y = (max_.y - ray.origin.y) / ray.direction.y; 
            //Berechnung des t von der y-min Seite

            if (t_min_y || t_max_y > 0) && 
            {
                glm::vec3 intersection_point_min_y = ray.origin + t_min_y * ray.direction;
                glm::vec3 intersection_point_max_y = ray.origin + t_max_y * ray.direction;
                //Schnittpunkt Berechnung für die Seite y-Min und y-Max
                    
                if ( ( (intersection_point_min_y.x <= max_.x && intersection_point_min_y.x >= min_.x) 
                    && (intersection_point_min_y.z <= max_.z && intersection_point_min_y.z >= min_.z))
                    || ((intersection_point_max_y.x <= max_.x && intersection_point_max_y.x >= min_.x) 
                    && (intersection_point_max_y.z <= max_.z && intersection_point_max_y.z >= min_.z)
                   ) )
                //Hier wird geprüft ob der Punkt in der Box liegt
                {
                    intersection = true; 
                    //Es gibt einen Schnittpunkt 

                    if (t_min_y < t_max_y)
                    {
                        std::cout << "Schnittpunkt bei der Distanz (y-min): " << t_min_y << endl; 
                        return t_min_y; 
                    }
                    else 
                    {
                        std::cout << "Schnittpunkt bei der Distanz (y-max): " << t_max_y << endl;
                        return t_max_y; 
                    }
                    //Ausgabe der kleinsten Distanz und somit den nächsten Schnittpunktes
                }
            }  
        }
    }

    if (ray.direction.z != 0) 
    {
        if (ray.direction.z > 0)
        {
            float t_min_z = (min_.z - ray.origin.z) / ray.direction.z;
            float t_max_z = (max_.z - ray.origin.z) / ray.direction.z; 
            //Berechnung des t von der z-min und z-max Seite

            if (t_min_z || t_max_z > 0)
            {
                glm::vec3 intersection_point_min_z = ray.origin + t_min_z * ray.direction;
                glm::vec3 intersection_point_max_z = ray.origin + t_max_z * ray.direction;
                //Schnittpunkt Berechnung für die Seite y-Min und y-Max
                    
                if ( ( (intersection_point_min_z.x <= max_.x && intersection_point_min_z.x >= min_.x) 
                    && (intersection_point_min_z.y <= max_.y && intersection_point_min_z.y >= min_.y))
                    || ((intersection_point_max_z.x <= max_.x && intersection_point_max_z.x >= min_.x) 
                    && (intersection_point_max_z.y <= max_.y && intersection_point_max_z.y >= min_.y)
                   ) )
                //Hier wird geprüft ob der Punkt in der Box liegt
                {
                    intersection = true; 
                    //Es gibt einen Schnittpunkt 

                    if (t_min_z < t_max_z)
                    {
                        std::cout << "Schnittpunkt bei der Distanz (z-min): " << t_min_z << endl; 
                        return t_min_z; 
                    }
                    else 
                    {
                        std::cout << "Schnittpunkt bei der Distanz (z-max): " << t_max_z << endl;
                        return t_max_z; 
                    }
                    //Ausgabe der kleinsten Distanz und somit den nächsten Schnittpunktes
                }
            } 
        } */

