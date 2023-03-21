#include "Records.hpp"

Record::Record(std::string id, std::string type)
    :id(id), type(type)
{
}

void Record::printRecord()
{
    std::cout<<"Type: "<< this->type<<" ID: "<<this->id<<std::endl;
}


Variable::Variable(std::string id, std::string type)
    :Record(id, type)
{
}