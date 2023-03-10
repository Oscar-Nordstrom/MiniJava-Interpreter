#include "StackMachine.hpp"

StackMachine::StackMachine()
{
}

void StackMachine::interprete(ByteCodeProgram *program)
{
    std::stack<int> theStack;
    for(auto m: program->methodsVec)
    {

    }
}
