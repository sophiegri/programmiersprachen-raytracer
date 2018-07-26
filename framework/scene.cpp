#include "scene.hpp"
#include <memory> //shared_ptr
#include <map>
#include <vector>
#include <set>
#include "shape.hpp"
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"

//Einlesen der SDF Datei 
Scene open_sdf (std::string const& sdf_name)
{
    Scene new_scene; 
    std::ifstream dat_ein;
    dat_ein.open(sdf_name);
    //ifstream darf nur in der Datei lesen
    std::string buffer; 

    while(std::getline(dat_ein, buffer))
    {
        std::stringstream line_stream (buffer);
        //liest die zeichen der Zeile als einzelne strings 
        std::string keyword; 
        
        line_stream >> keyword; 
        if ("define" == keyword)
        {
        //MATERIAL einlesen 
            line_stream >> keyword; 
            if ("material" == keyword)
            {
                std::shared_ptr<Material> new_material_ptr = std::make_shared<Material> ();
                //Objekt vom Typ shared pointer Material 
                line_stream >> new_material_ptr->name; 
                //bei pointern dereferenzieren ->
                line_stream >> new_material_ptr->ka.r; 
                line_stream >> new_material_ptr->ka.g; 
                line_stream >> new_material_ptr->ka.b; 
                line_stream >> new_material_ptr->kd.r; 
                line_stream >> new_material_ptr->kd.g;
                line_stream >> new_material_ptr->kd.b;
                line_stream >> new_material_ptr->ks.r; 
                line_stream >> new_material_ptr->ks.g;
                line_stream >> new_material_ptr->ks.b;
                line_stream >> new_material_ptr->m_exponent; 
                //Hier wird jedes durch ein whitespace getrenntes string/float etc. (wird selbstständig interpretiert)
                //in den jeweiligen Variablen gespeichert 

                std::cout << *new_material_ptr << "\n";
                //Ausgabe auf der Konsole 

                (new_scene.material_map).insert(make_pair(new_material_ptr->name, new_material_ptr));
                //Speichern des neuen Materials in einer Map mit dem namen des Materials als key 
                //und einem pointer auf dieses Material als value 
                (new_scene.material_set).insert(new_material_ptr);
                (new_scene.material_vector).push_back(new_material_ptr);
            }

            //SHAPE einlesen 
            if ("shape"==keyword)
            {
                line_stream >> keyword; 
                
                if ("box" == keyword) 
                {
                    auto new_box_ptr = std::make_shared<Box>(); 
                
                    line_stream >> new_box_ptr->name_;
                    line_stream >> new_box_ptr->min_.x; 
                    line_stream >> new_box_ptr->min_.y; 
                    line_stream >> new_box_ptr->min_.z; 
                    line_stream >> new_box_ptr->max_.x; 
                    line_stream >> new_box_ptr->max_.y; 
                    line_stream >> new_box_ptr->max_.z; 
                    
                    auto m = make_shared <Material> (); 
                    line_stream >> m->name;
                    new_box_ptr->m_ = m; 
                    //um das Material einzulesen, brauchen wir einen make_shared pointer der das Material referenziert 
                    //m_ ist material aus der Shape 

                    std::cout << *new_box_ptr << "\n"; 
                }
             
                if ("sphere" == keyword)
                {
                    auto new_sphere_ptr = std::make_shared<Sphere>();

                    line_stream >> new_sphere_ptr->name_; 
                    line_stream >> new_sphere_ptr->center_.x; 
                    line_stream >> new_sphere_ptr->center_.y; 
                    line_stream >> new_sphere_ptr->center_.z; 
                    line_stream >> new_sphere_ptr->radius_; 
                    auto m = make_shared <Material> (); 
                    line_stream >> m->name; 
                    new_sphere_ptr->m_ = m; 

                    std::cout << *new_sphere_ptr << "\n"; 
                }          
            }
        
        }
    }
    dat_ein.close(); 
    return new_scene; 
}
//Aufgabe 6.5 find functions

material_ptr map_find (std::string const& eingabe, std::map<std::string, std::shared_ptr<Material>> const& material_map)
{
    auto it = material_map.find(eingabe);
    //Variable it geht durch die Map und sucht nach Eingabe 
    if (it != material_map.end() )
    {
        std::cout << "Material " << eingabe << " exists." << endl; 
        return it->second;
        //first ist key, second ist value  
    }
    else 
    {
        std::cout << "Material " << eingabe << " doesn't exists." << endl;
        return nullptr; 
    }
}

material_ptr set_find (std::string const& eingabe, std::set<std::shared_ptr<Material>> const& material_set)
{
  auto it = find_if(material_set.begin(), material_set.end(), 
            [&eingabe] (std::shared_ptr<Material> const& material) 
            {return (material->name)==eingabe; }); 
            //capture ist die Eingabe von außerhalb die nichts mit container zu tun hat, aber gebraucht wird
            //der funktion wird ein shared_ptr gegeben mit dem über das set gegangen wird
            //nur wenn der name des shared_ptr der mit den shared_ptr in dem set verglichen wird, gleich der eingabe ist wird returnt
            //Lambda 
            
        if(it!= material_set.end())
        //wenn es nicht am Ende ist, dann wurde was gefunden, das soll zurückgegeben werden 
        {
            std::cout << "Material " << eingabe << " exists." << endl; 
            return *it;
            //* dereferenziert den pointer des iterators und gibt den shared_pointer zurück 
        }
        else
        {
            std::cout << "Material " << eingabe << " doesn't exists." << endl;
            return nullptr;
        }
} 


material_ptr vector_find (std::string const& eingabe, std::vector<std::shared_ptr<Material>> const& material_vector)
{     
    auto it = find_if(material_vector.begin(), material_vector.end(), 
                [&eingabe] (std::shared_ptr<Material> const& material) 
                {return (material->name)==eingabe; }
                ); 
    
     if(it!= material_vector.end())
        //wenn es nicht am Ende ist, dann wurde was gefunden, das soll zurückgegeben werden 
        {
            std::cout << "Material " << eingabe << " exists." << endl; 
            return *it;
            //* dereferenziert den pointer des iterators und gibt den shared_pointer zurück 
        }
        else
        {
            std::cout << "Material " << eingabe << " doesn't exists." << endl;
            return nullptr;
        }
}
 