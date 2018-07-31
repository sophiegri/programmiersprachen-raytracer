#include "shape.hpp"


Shape::Shape():
    name_{"Default-Name"},
    m_{}
    {}

Shape::Shape(std::shared_ptr<Material> const& material, std::string const& name):
    m_{material},
    name_{name}
    {}


Shape::~Shape() 
{
    //std::cout << "Destructor Shape: " << name_ << "!" << "\n";
}

std::ostream& Shape::print(std::ostream& os) const
{
    os  << "Name: "  << name_ << endl
        << "Material Name: " << m_->name << endl
        << "Koeffizient a: " << m_->ka.r << ", " << m_->ka.g << ", " << m_->ka.b << endl
        << "Koeffizient s: " << m_->ks.r << ", " << m_->ks.g << ", " << m_->ks.b << endl
        << "Koeffizient d: " << m_->kd.r << ", " << m_->kd.g << ", " << m_->kd.b << endl
        << "Spekularreflexionsexponent: " << m_->m_exponent << endl; 
        return os;          
}

std::ostream& operator<<(std::ostream& os, Shape const& sha)
{
    std::ostream::sentry const ostream_sentry(os);
    return ostream_sentry ? sha.print(os) : os; 
}
