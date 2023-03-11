#include <iostream>

#include "FileReader.hpp"
#include "StackMachine.hpp"

int main()
{
    // std::cout<<"Expected output from file E.java:\n";
    // int one = (4 * 2) + 10 - 2 * 6 + (4 - 1) * 2 / 2;
    // bool two = true == (!true && false) || 10 > 1 && 1 < 10;
    // std::cout<<one<<std::endl;
    // std::cout<<two<<std::endl;
    FileReader fr;
    StackMachine sm;
    ByteCodeProgram* prog = fr.ReadFile();
    //fr.printProgram(prog);
    //std::cout<<"Actual output from file E.java:\n";
    sm.interprete(prog);

    return 0;
}