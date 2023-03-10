#pragma once

#include <stack>

#include "ByteCode.hpp"

class StackMachine
{
public:
    StackMachine();
    void interprete(ByteCodeProgram* program);

};