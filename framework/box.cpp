#include "box.hpp"

//Konstruktoren 

Box::Box(): 
min_{0.0f, 0.0f, 0.0f},
max_{1.0f, 1.0f, 1.0f}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
min_{min},
max_{max}
{}

Box::~Box() {}

//Methoden 

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
