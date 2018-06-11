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

    //Get-Methoden
    glm::vec3 const& get_min(); //warum nochmal const& ??
    glm::vec3 const& get_max(); 

    //virtual Methoden aus Shape
    float area() const override; //override versichert dass in der Basisklasse eine virtuelle Methode mit dem selben Namen & Signatur gibt 
    float volume() const override;

    private: 
    glm::vec3 max_; 
    glm::vec3 min_; 

}; 

#endif //BOX_HPP