#pragma once

#include <stack>
#include <unordered_map>

#include "ByteCode.hpp"
#include "Variable.hpp"

class StackMachine
{
public:
    StackMachine();
    void interprete(ByteCodeProgram* program);
private:
    ByteCodeMethod* getMain(ByteCodeProgram* program);
    Variable* getVar(ByteCodeMethod* method, std::string var);
    void handleInstruction(std::stack<int>* theStack, std::unordered_map<std::string, int>* localVars,  ByteCodeMethod* method, ByteCodeInstruction* instruction);
    void handleArgument(std::stack<int>* theStack, std::unordered_map<std::string, int>* localVars, ByteCodeMethod* method, ByteCodeInstruction* instruction, ByteCode* argument);
    int getWhat(std::string what);
    void handleArgumentOp(std::stack<int>* theStack, InstructionType type);
    std::string getTypeString(InstructionType type);
    InstructionType getStringType(std::string type);
};