/* #include "composite.hpp"
#include <iostream> 

Composite::Composite(): 
Shape(), 
name_{"default_composite"}, 
composite_list{}
{}

Composite::Composite(std::string const& name, std::list <shared_ptr<Shape>> const& composite);
Shape(), 
name_{name},
composite_list{composite}
{}

void Composite::add() const
{

}

/* void Composite::get_children() const
{
    return 

} */ 