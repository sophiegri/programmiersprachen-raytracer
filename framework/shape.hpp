#ifndef SHAPE_HPP
#define SHAPE_HPP 
#include <glm/vec3.hpp>
#include "color.hpp"
#include "material.hpp"
#include "ray.hpp"
#include <string> // std::string 

class Shape 
{

    public:
    Shape(); 
    Shape(Color const& color, std::string const& name);

    virtual float area() const = 0; //hier wird noch nicht implementiert
    virtual float volume() const = 0; //wir können kein statisches/dynamisches Objekt von Shape anlegen sondern nur ein Pointer/Referenz
    virtual bool intersect(Ray const& ray, float& t) const = 0;

    //virtual 
     ~Shape(); //Destruktor

    virtual std::ostream& print(std::ostream& os) const;
    

    protected: //die abgeleiteten Klassen erben diese Member als private
    Color color_; 
    //std::shared_ptr<Material>; ?????
    std::string name_; 
}; 


std::ostream& operator<<(std::ostream& os, Shape const& s);


#endif //SHAPE_HPP

//eine abstrakte Basisklasse dient als Spezifikation für die abgeleitete Klasse
//sie bestimmt das Verhalten, das in den abgeleiteten Klassen implementiert wird

//rein virtuelle Methoden sind auch abstrakte Methoden, die nicht implementiert sind
//diese Methoden müssen überschrieben werden um ein Objekt einer abgeleiteten Klasse instanziieren zu können
//eine Klasse mit mind. einer pure virtual Methode kann nicht instantiiert werden