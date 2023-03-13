#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "ByteCode.hpp"

class FileReader
{
public:
    FileReader();
    ByteCodeProgram* ReadFile(std::string fileName = "byte_code.txt");
    void printProgram(ByteCodeProgram* program);
private:
    std::string getTypeString(InstructionType type);
    InstructionType getStringType(std::string type);
};