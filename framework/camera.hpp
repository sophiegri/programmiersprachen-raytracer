#ifndef CAMERA_HPP
#define CAMERA_HPP

struct Camera
{
    std::string name_ = {"default Camera_name"};
    glm::vec3 position_ = {0,0,0}; 
    float angle_ = {0.0f}; 

    friend std::ostream& operator<< (std::ostream& os, Camera const& c)
    {
        os << "Camera Name: " << c.name_ << endl
           << "Position: " << c.position_.x << ", " << c.position_.y << ", " << c.position_.z << endl
           << "Camera Angle: " << c.angle_ << endl; 
        return os; 
    } 
};


#endif //CAMERA_HPP