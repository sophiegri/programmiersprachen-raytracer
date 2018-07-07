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

//Datentransferobjekt Scene 
struct Scene
{
    std::string name = "default scene_name"; 

    std::map<std::string, std::shared_ptr<Material>> material_map; 
    std::vector<std::shared_ptr<Material>> material_vector; 
    std::set<shared_ptr<Material>> material_set; 
};

Scene open_sdf (std::string const& sdf_name);
//Der Rückgabetyp ist eine Scene 

#endif //SCENE_HPP