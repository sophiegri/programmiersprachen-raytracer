#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <iostream>
#include "color.hpp"
#include <string> // std::string
using namespace std;

//Datentransferobjekt Material 
struct Material
{
    std::string name = "default material_name"; 
    //Materialkoeffizienten
    Color ka {0.0f, 0.0f, 0.0f}; 
    Color kd {0.0f, 0.0f, 0.0f}; 
    Color ks {0.0f, 0.0f, 0.0f};    
    //Spekularreflexionsexponenten
    float m_exponent = 0.0f; 


 friend std::ostream& operator<< (std::ostream& os, Material const& m)
    {
        os << "Material Name: " << m.name << endl
           << "Koeffizient a: " << m.ka.r << ", " << m.ka.g << ", " << m.ka.b << endl
           << "Koeffizient s: " << m.ks.r << ", " << m.ks.g << ", " << m.ks.b << endl
           << "Koeffizient d: " << m.kd.r << ", " << m.kd.g << ", " << m.kd.b << endl
           << "Spekularreflexionsexponent: " << m.m_exponent << endl; 
        return os; 
    }

};

#endif //MATERIAL_HPP