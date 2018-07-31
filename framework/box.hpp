#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape //eine Klasse Box von der Basisklasse Shape
{
    public: 

    //Konstruktoren
    Box(); 
    Box(glm::vec3 const& min, glm::vec3 const& max); 
    Box(std::shared_ptr<Material> const& material, std::string const& name, glm::vec3 const& min, glm::vec3 const& max); 
    //~Box(); //override; 

    //Get-Methoden
    glm::vec3 get_min() const; 
    glm::vec3 get_max() const; 


    //virtual Methoden aus Shape
    float area() const override; //override versichert dass in der Basisklasse eine virtuelle Methode mit dem selben Namen & Signatur gibt 
    float volume() const override;
    bool intersect(Ray const& ray, float& t) const override; 

    glm::vec3 get_center() const override; 
    float get_radius() const override; 
    glm::vec3 get_normal(glm::vec3 const& intersect) const override; 

    std::ostream& print (std::ostream& os) const override;

    //private: 
    glm::vec3 max_; 
    glm::vec3 min_; 

}; 

std::ostream& operator<< (std::ostream& os, const Box& b);

#endif //BOX_HPP