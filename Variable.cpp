#include "Variable.hpp"

Variable::Variable()
    : Record("", "") 
{
}

Variable::Variable(std::string type, std::string id)
    : Record(type, id) {}

void Variable::print(int count)
{
    for(int i = 0; i < count; i++)
    {
        std::cout<<" ";
    }
    std::cout<<"Record: Variable. TYPE: "<<this->getType()<<" ID: "<<this->getID()<<std::endl;
}
