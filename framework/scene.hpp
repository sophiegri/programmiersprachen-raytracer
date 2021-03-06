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
#include "light.hpp"
#include "camera.hpp"
#include "shape.hpp"
#include <algorithm>

using material_ptr = std::shared_ptr<Material>; 
using shape_ptr = std::shared_ptr<Shape>; 
//um auf unseren material_ptr zu verweisen 

//Datentransferobjekt Scene 
struct Scene
{
    std::string name = "default scene_name"; 

    std::map<std::string, std::shared_ptr<Material>> material_map; 
    std::vector<std::shared_ptr<Shape>> shape_vector;
    std::vector<std::shared_ptr<Light>> light_vector; 
    Camera camera;
    Color ambient {1.0f,1.0f,1.0f};
     
};

Scene open_sdf (std::string const& sdf_name);
//Der Rückgabetyp ist eine Scene 
 
std::shared_ptr<Material> find_material (std::string const& eingabe, std::map<std::string, std::shared_ptr<Material>> const& material_map);
std::shared_ptr<Shape> find_shape (std::string const& eingabe, std::vector<std::shared_ptr<Shape>> const& shape_vector); 

#endif //SCENE_HPP