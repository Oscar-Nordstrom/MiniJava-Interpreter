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

    int sum, num;
    num = 100;
    sum = 0;
    while (0 < num) {
      sum = sum + num;
      num = num - 1;
    }
    std::cout<<"Expected: "<<sum<<std::endl;


    Interpreter ir(prog);
    ir.execute();


    return 0;
}