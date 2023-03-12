#include <iostream>

#include "FileReader.hpp"
#include "StackMachine.hpp"
#include "Interpreter.hpp"

int main()
{
    FileReader fr;
    //StackMachine sm;
    ByteCodeProgram* prog = fr.ReadFile();
    //fr.printProgram(prog);
    //sm.interprete(prog);

    Interpreter ir(prog);
    ir.execute();


    return 0;
}