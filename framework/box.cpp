#include "box.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp> 
#include <vector>
#include <iostream>
#include "plane.hpp"
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


std::shared_ptr<Hit> Box::intersect(Ray const& ray) const {

    Plane plane1 {min_, glm::vec3 {-1,0,0}}; 
    Plane plane2 {min_, glm::vec3 {0,0,-1}}; 
    Plane plane3 {min_, glm::vec3 {0,-1,0}}; 
    Plane plane4 {max_, glm::vec3 {1,0,0}}; 
    Plane plane5 {max_, glm::vec3 {0,0,1}}; 
    Plane plane6 {max_, glm::vec3 {0,1,0}}; 

    float distance1 = (glm::dot(plane1.normal, plane1.origin) - glm::dot(ray.origin, plane1.normal)) / (glm::dot(ray.direction, plane1.normal));
    float distance2 = (glm::dot(plane2.normal, plane2.origin) - glm::dot(ray.origin, plane2.normal)) / (glm::dot(ray.direction, plane2.normal));
    float distance3 = (glm::dot(plane3.normal, plane3.origin) - glm::dot(ray.origin, plane3.normal)) / (glm::dot(ray.direction, plane3.normal));
    float distance4 = (glm::dot(plane4.normal, plane4.origin) - glm::dot(ray.origin, plane4.normal)) / (glm::dot(ray.direction, plane4.normal));
    float distance5 = (glm::dot(plane5.normal, plane5.origin) - glm::dot(ray.origin, plane5.normal)) / (glm::dot(ray.direction, plane5.normal));
    float distance6 = (glm::dot(plane6.normal, plane6.origin) - glm::dot(ray.origin, plane6.normal)) / (glm::dot(ray.direction, plane6.normal));

	std::vector<glm::vec3> hit_points;
	std::vector<glm::vec3> hit_normals;
    glm::vec3 cut_point; 

	//Checking for each plane if it is in front of the camera
	if (distance1 > 0) {
		cut_point = ray.origin + distance1 * ray.direction;
		if (cut_point.y < max_.y && cut_point.y > min_.y && cut_point.z < max_.z && cut_point.z > min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(plane1.normal);
		}
	}
	if (distance4 > 0) {
		cut_point = ray.origin + distance4 * ray.direction;
		if (cut_point.y < max_.y && cut_point.y > min_.y && cut_point.z < max_.z && cut_point.z > min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(plane4.normal);
		}
	}
	//untere Flaeche
	if (distance2 > 0){
		cut_point = ray.origin + distance2 * ray.direction;
		if (cut_point.y < max_.y && cut_point.y > min_.y && cut_point.x < max_.x && cut_point.x > min_.x) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(plane2.normal);
		}
	}
	//obere Flaeche
	if (distance5 > 0) {
		cut_point = ray.origin + distance5 * ray.direction;
        //std::cout << min_.x << " ; " << min_.y << " ; " << min_.z << "\n";
		if (cut_point.y < max_.y && cut_point.y > min_.y && cut_point.x < max_.x && cut_point.x > min_.x) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(plane5.normal);
		}
	}
	if (distance3 > 0) {
		cut_point = ray.origin + distance3 * ray.direction;
		if (cut_point.x < max_.x && cut_point.x > min_.x && cut_point.z < max_.z && cut_point.z > min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(plane3.normal);
		}
	}
	if (distance6 > 0) {
		cut_point = ray.origin + distance6 * ray.direction;
		if (cut_point.x < max_.x && cut_point.x > min_.x && cut_point.z < max_.z && cut_point.z > min_.z) {
			hit_points.push_back(cut_point);
			hit_normals.push_back(plane6.normal);
		}
	}

	//selecting the cut that is closest to the camera
	if (hit_points.size() > 0) {
		glm::vec3 closest_hit = hit_points.at(0);
		glm::vec3 closest_normal = hit_normals.at(0);

		for (auto it = 0; it < hit_points.size(); ++it) {
			if (glm::length(hit_points.at(it) - ray.origin) < glm::length(closest_hit - ray.origin)) {
				closest_hit = hit_points.at(it);
				closest_normal = hit_normals.at(it);
			}
		}
/* 		glm::vec4 transformed_cut = world_transformation_ * glm::vec4{ closest_hit, 1 };
		glm::vec4 transformed_normal = glm::normalize(glm::transpose(world_transformation_inv_) * glm::vec4{ closest_normal , 0 }); 
		cut_point = glm::vec3{ transformed_cut.x, transformed_cut.y, transformed_cut.z };
		normal = glm::vec3{transformed_normal.x, transformed_normal.y, transformed_normal.z}; 
		shape = std::make_shared<Box>(min_, max_, name(), material()); */
       
       //std::cout << min_.x << " ; " << min_.y << " ; " << min_.z << "\n";
		return std::make_shared <Hit> (Hit{closest_hit, closest_normal});
	}
	return nullptr;
};






 /* bool Box::intersect(Ray const& ray, float& distance) const
 {
     distance = std::numeric_limits<float>::max();
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
                         if (t_min_x < distance)
                         //ist das t von x-min kleiner als mein ursprüngliches t 
                        {
                            distance = t_min_x;
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
                         if (t_max_x < distance) 
                         {
                            distance = t_max_x;
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
                         if (t_min_y < distance) 
                        {
                            distance = t_min_y;
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
                         if (t_max_y < distance) 
                         {
                            distance = t_max_y;
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
                         if (t_min_z < distance) 
                        {
                            distance = t_min_z;
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
                         if (t_max_z < distance) 
                         {
                            distance = t_max_z;
                            intersection = true;  
                         }
                    }               
                }
            }
        }
        return intersection;
    }
 */