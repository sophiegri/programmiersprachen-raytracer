#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape
{
    public: 

    //Konstruktoren
    Sphere(); 
    Sphere(glm::vec3 const& center, float const& radius); 
    ~Sphere() override; 

    //get-Methoden
    glm::vec3 get_center() const; 
    float get_radius() const; 
 
    //virtuelle Methoden aus Shape
    float area() const override; 
    float volume() const override;

    private: 
    glm::vec3 center_; 
    float radius_; 
};

#endif //SPHERE_HPP