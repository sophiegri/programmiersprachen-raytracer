#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "ray.hpp"
#include <glm/vec3.hpp>
#include <iostream>
#include <cmath>


struct Camera
{
    std::string name_ = {"default Camera_name"};
    glm::vec3 origin_ = {0,0,0};
    glm::vec3 position_ = {0,0,0}; 
    float angle_ = {0.0f}; 



    Ray shoot_ray (float x, float y, float width, float height) const
    {
        glm::vec3 ray_origin = {0,0,0};
        glm::vec3 ray_direction = { ((x-width)/2), ((y-height)/2), (-(width/2)/(tan(angle_/2)))};
        return Ray{ray_origin, ray_direction}; 
    }


    friend std::ostream& operator<< (std::ostream& os, Camera const& c)
    {
        os << "Camera Name: " << c.name_ << endl
           << "Position: " << c.position_.x << ", " << c.position_.y << ", " << c.position_.z << endl
           << "Camera Angle: " << c.angle_ << endl; 
        return os; 
    } 
};


#endif //CAMERA_HPP