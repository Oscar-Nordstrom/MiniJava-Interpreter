#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "ByteCode.hpp"

class FileReader
{
public:
    FileReader();
    ByteCodeProgram* ReadFile();
private:
    std::string getTypeString(InstructionType type);
    InstructionType getStringType(std::string type);
};