#include "scene.hpp"
#include <memory> //shared_ptr
#include "material.hpp"

Scene open_sdf (std::string const& sdf_name)
{
    Scene scene1; 
    std::ifstream dat_ein(sdf_name);
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
                //Objekt vom Typ Material 
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

                std::cout << new_material_ptr->name << ", " << endl; 
                std::cout << new_material_ptr->ka.r << ", " << new_material_ptr->ka.g << ", " << new_material_ptr->ka.b << endl; 
                std::cout << new_material_ptr->kd.r << ", " << new_material_ptr->kd.g << ", " << new_material_ptr->kd.b << endl;
                std::cout << new_material_ptr->ks.r << ", " << new_material_ptr->ks.g << ", " << new_material_ptr->ks.b << endl;
                std::cout << new_material_ptr->m_exponent << endl; 
                //Ausgabe auf der Konsole 

                (scene1.material_map).insert(make_pair(new_material_ptr->name, new_material_ptr));
                //Speichern des neuen Materials in einer Map mit dem namen des Materials als key und einem pointer auf dieses Material
                //als value 
            }
        }
    }
    return scene1; 
}