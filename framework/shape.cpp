#include "shape.hpp"


//Konstruktoren 

Shape::Shape():
name_{"default name"},
color_{0.5f,0.5f,0.5f}
{}

Shape::Shape(Color const& color, std::string const& name):
color{color_},
name{name_}
{}

Shape::~Shape() {}

std::ostream& Shape::print(std::ostream& os) const
{
    
}