#include "Record.hpp"

Record::Record(std::string type, std::string id)
    :type(type), id(id)
{}

std::string Record::getID(){return this->id;}

std::string Record::getType(){return this->type;}

std::string Record::getData()
{
    std::string ret = "Type: "+ this->type + " ID: " + this->id;
    return ret;
}

void Record::setID(std::string id){this->id = id;}

void Record::setType(std::string type){this->type = type;}

void Record::printData(){std::cout<<"Type: "<< this->type<<" ID: "<<this->id<<std::endl;}
