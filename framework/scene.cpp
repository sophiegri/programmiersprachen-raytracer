#include "scene.hpp"
#include <memory> //shared_ptr
#include <map>
#include <vector>
#include <set>
#include "material.hpp"


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

                std::cout << "Name:" << new_material_ptr->name << "; " 
                << "Ka:" << new_material_ptr->ka.r << "," << new_material_ptr->ka.g << "," << new_material_ptr->ka.b << "; "
                << "Kd:" << new_material_ptr->kd.r << "," << new_material_ptr->kd.g << "," << new_material_ptr->kd.b << "; "
                << "Ks:" << new_material_ptr->ks.r << "," << new_material_ptr->ks.g << "," << new_material_ptr->ks.b << "; "
                << "Spekularreflexionsexponent: " << new_material_ptr->m_exponent << "\n\n"; 
                //Ausgabe auf der Konsole 

                (new_scene.material_map).insert(make_pair(new_material_ptr->name, new_material_ptr));
                //Speichern des neuen Materials in einer Map mit dem namen des Materials als key 
                //und einem pointer auf dieses Material als value 
                (new_scene.material_set).insert(new_material_ptr);
                (new_scene.material_vector).push_back(new_material_ptr);
            }
        }
    };
    dat_ein.close(); 
    return new_scene; 
}

material_ptr map_find (std::string const& eingabe, std::map<std::string, std::shared_ptr<Material> > material_map)
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

material_ptr set_find (std::string const& eingabe, std::set<std::shared_ptr<Material>> material_set)
{
  auto it = find(material_set.begin(), material_set.end(), 
            [&eingabe] (std::shared_ptr<Material> const& m)
            { 
                return (m->name)==eingabe; 
            }); 
            //Lambda 
            
        if(it!= material_set.end())
        {
            std::cout << "Material " << eingabe << " exists." << endl; 
            return *it;
        }
        else
        {
            std::cout << "Material " << eingabe << " doesn't exists." << endl;
            return nullptr;
        }
} 

 