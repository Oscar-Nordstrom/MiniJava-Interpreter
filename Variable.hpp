#pragma once
#include <string>
#include <iostream>

#include "Record.hpp"

class Variable : public Record
{
public:
    Variable();
    Variable(std::string type, std::string id);
    virtual ~Variable(){};

    void print(int count);
};