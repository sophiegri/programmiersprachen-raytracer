#include "shape.hpp"


Shape::Shape():
name_{"Default-Name"},
color_{0.5f,0.5f,0.5f}
{
    std::cout << "Standard-Constructor Shape: " << name_ << "!" << "\n";
}

Shape::Shape(Color const& color, std::string const& name):
color_{color},
name_{name}
{
    std::cout << "Constructor Shape: " << name_ << "!" << "\n";
}

Shape::~Shape() 
{
    std::cout << "Destructor Shape: " << name_ << "!" << "\n";
}

std::ostream& Shape::print(std::ostream& os) const
{
    os  << "Name: "  
        << name_ << "\n"
        << "Farbe: "
        << color_.r << " , "
        << color_.g << " , " 
        << color_.b << "\n";        
    return os; 
}

std::ostream& operator<<(std::ostream& os, Shape const& sha)
{
    std::ostream::sentry const ostream_sentry(os);
    return ostream_sentry ? sha.print(os) : os; 
}