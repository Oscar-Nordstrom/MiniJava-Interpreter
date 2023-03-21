#include <iostream>
#include <stdlib.h>

#include "FileReader.hpp"
#include "Interpreter.hpp"



void doFile(int num);
bool checkInput(std::string& input);

int main()
{
    
    
    std::string input;
    std::cout<<"Choose what file to interpret:\n0: Current\n1: E.java\nPresse anyting else to exit\n";
    while(checkInput(input))
    {
      std::cout<<"\nOutput:\n";
      doFile(std::stoi(input));
      std::cout<<"Press any Enter to continue";
      std::cin.ignore();
      std::cin.get();
      system("clear");
      std::cout<<"Choose what file to interpret:\n0: Current\n1: E.java\nPresse anyting else to exit\n";
    }

    return 0;
}

bool checkInput(std::string& input)
{
  
  std::cin>>input;
  if(input == "0"
  ||input == "1")
  {
    return true;
  }
  return false;
}

void doFile(int num)
{
  std::string name;
  switch (num)
  {
  case 0:
    name = "byte_code.txt";
    break;
  case 1:
    name = "test_bytecode/E.txt";
    break;
  }
  FileReader fr;
  ByteCodeProgram* prog = fr.ReadFile(name);
  //fr.printProgram(prog);
  Interpreter ir(prog);
  ir.execute();
}