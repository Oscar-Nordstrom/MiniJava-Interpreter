#pragma once

#include <string>
#include <iostream>

class Record
{
public:
    Record(std::string id = "Empty", std::string type = "Empty");
    std::string id;
    std::string type;
    //Getters/setters
    void printRecord();
};

class Variable : public Record
{
public:
    Variable(std::string id = "Empty", std::string type = "Empty");
};