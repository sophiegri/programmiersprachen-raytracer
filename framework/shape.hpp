#ifndef SHAPE_HPP
#define SHAPE_HPP 
#include <glm/vec3.hpp>

class Shape 
{
    public:
    virtual float area() const = 0; //hier wird noch nicht implementiert
    virtual float volume() const = 0; 
}; 


#endif //SHAPE_HPP

//eine abstrakte Basisklasse dient als Spezifikation für die abgeleitete Klasse
//sie bestimmt das Verhalten, das in den abgeleiteten Klassen implementiert wird

//rein virtuelle Methoden sind auch abstrakte Methoden, die nicht implementiert sind
//diese Methoden müssen überschrieben werden um ein Objekt einer abgeleiteten Klasse instanziieren zu können
//eine Klasse mit mind. einer pure virtual Methode kann nicht instantiiert werden