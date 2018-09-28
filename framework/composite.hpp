/* #ifndef COMPOSITE_HPP
#define COMPOSITE_HPP
#include "shape.hpp"
#include <iostream>
#include <string> // std::string

class Composite : public Shape 
{
    public: 
    Composite(); 
    Composite(std::string const& name, std::list <shared_ptr<Shape>> const& composite); 

    void add(std::shared:ptr<Shape>) const; 
    void remove(std::shared:ptr<Shape>) const; 
    void get_children() const; 

    private:
    std::string name_; 
    std::list <shared_ptr<Shape>> composite_list; 
};



#endif //COMPOSITE_HPP  */