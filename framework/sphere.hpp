#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape
{
    public: 

    //Konstruktoren
    Sphere(); 
    Sphere(Color const& color, std::string const& name, glm::vec3 const& center, float radius);

    //Default Werte um die Größe des Sphere zu setzen, ähnlich wie Standardkonstruktor 
    //auto default_sized_sphere = Sphere(glm::vec3(1.0, 7.0, 2.0));
    //auto default_sized_sphere = Sphere(glm::vec3(1.0, 7.0, 2.0), 7.0);

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