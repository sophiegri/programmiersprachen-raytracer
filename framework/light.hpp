#ifndef LIGHT_HPP 
#define LIGHT_HPP
#include <iostream>
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{
    std::string name = "default light_name";
    Color color {0.2f, 0.2f, 0.2f}; 
    glm::vec3 position {1000, 700, 0};
    float brightness = 100; 

    float get_intensity (Color const& color, float brightness)
    {
        auto I = ((color.r * brightness) + (color.g * brightness) + (color.b * brightness));
        return I; 
    }


    friend std::ostream& operator<< (std::ostream& os, Light const& l)
    {
        os << "Light Name: " << l.name << endl
           << "Color: " << l.color.r << ", " << l.color.g << ", " << l.color.b << endl
           << "Position: " << l.position.x << ", " << l.position.y << ", " << l.position.z << endl
           << "Brightness: " << l.brightness << endl; 
        return os; 
    }
};

#endif //LIGHT_HPP
