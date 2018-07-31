#ifndef LIGHT_HPP 
#define LIGHT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{
    std::string name_ = "default light_name";
    Color color_ {0.0f, 0.0f, 0.0f}; 
    glm::vec3 position_ {0,0,0};
    unsigned int brightness_ {0};
    Color intensity_ = get_intensity(color_, brightness_);

    

    Color get_intensity (Color const& color, unsigned int brightness)
    {
        Color i (color.r*brightness, color.g*brightness, color.b*brightness);
        return i; 
    } 


    friend std::ostream& operator<< (std::ostream& os, Light const& l)
    {
        os << "Light Name: " << l.name_ << endl
           << "Color: " << l.color_.r << ", " << l.color_.g << ", " << l.color_.b << endl
           << "Position: " << l.position_.x << ", " << l.position_.y << ", " << l.position_.z << endl
           << "Brightness: " << l.brightness_ << endl; 
        return os; 
    } 
};

#endif //LIGHT_HPP
