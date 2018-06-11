#include "box.hpp"

//Konstruktoren 

Box(): 
min_{0},
max_{1}
{}

Box(glm::vec3 const& min, glm::vec3 const& max):
min_{min},
max_{max}
{}

//Methoden 

glm::vec3 const& get_min() const 
{
    return min_; 
}

glm::vec3 const& get_max() const 
{
    return max_; 
}

float area() const override
{
 //not implemented yet
}

float volume() const override
{
 //not implemented yet
}

