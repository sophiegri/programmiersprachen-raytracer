#ifndef SCENE_HPP
#define SCENE_HPP
#include <iostream> //std::cout 
#include <string>
#include <fstream> //std::ifstream 
#include <sstream> 
#include <map> //std::map
#include <vector> // std::vector 
#include <set> // std::set 
#include <memory> // std::shared_ptr 
#include "material.hpp"
#include <algorithm>

using material_ptr = std::shared_ptr<Material>; 
//um auf unseren material_ptr zu verweisen 

//Datentransferobjekt Scene 
struct Scene
{
    std::string name = "default scene_name"; 

    std::map<std::string, std::shared_ptr<Material>> material_map; 
    std::vector<std::shared_ptr<Material>> material_vector; 
    std::set<shared_ptr<Material>> material_set; 
};

//Aufgabe 6.5 open sdf & find function 
Scene open_sdf (std::string const& sdf_name);
//Der Rückgabetyp ist eine Scene 
 

material_ptr map_find (std::string const& name, std::map<std::string, std::shared_ptr<Material>> material_map);
material_ptr set_find (std::string const& name, std::set<shared_ptr<Material>> material_set);
material_ptr vector_find (std::string const& name, std::vector<std::shared_ptr<Material>> material_vector);


#endif //SCENE_HPP