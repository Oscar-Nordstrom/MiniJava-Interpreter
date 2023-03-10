#include <iostream>

#include "FileReader.hpp"
#include "StackMachine.hpp"

int main()
{
    FileReader fr;
    StackMachine sm;
    sm.interprete(fr.ReadFile());
    return 0;
}