#pragma once

#include <unordered_map>
#include <stack>

#include "Variable.hpp"
#include "ByteCode.hpp"

class Activation
{
public:
    Activation(int ic, int ac, ByteCodeMethod* method);
    ByteCode* getNext();
public:
    int instructionCounter;
    int argumentCounter;
    std::unordered_map<std::string, int> local_vars;
    ByteCodeMethod* method;
private:

};

class Interpreter
{
public:
    Interpreter(ByteCodeProgram* program);
    ByteCodeMethod* getMain();
    void execute();
public:
    ByteCodeProgram* program;
    ByteCodeMethod* mainMethod;
    std::stack<int> dataStack;
private:
    void handleArgumentOp(InstructionType instruction);
    int getWhat(std::string what);
};