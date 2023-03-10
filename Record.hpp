#pragma once
#include <string>
#include <iostream>

class Record
{
public:
    Record()=default;
    Record(std::string type, std::string id);
    virtual ~Record(){};
    std::string getID();
    std::string getType();
    std::string getData();
    void setID(std::string id);
    void setType(std::string type);
    void printData();
    
    std::string id;
    std::string type;
};