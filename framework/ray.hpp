#ifndef RAY_HPP
#define RAY_HPP
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

//Datentransferobjekt Ray 
struct Ray 
{
    glm::vec3 origin = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, -1.0f};

    Ray (): 
    origin {0.0f, 0.0f, 0.0f},
    direction {0.0f, 0.0f, -1.0f}
    {}
        
    Ray(glm::vec3 origin_, glm::vec3 direction_):
    origin{origin_},
    direction{ glm::normalize(direction_) } {}

};

#endif //RAY_HPP