#include <iostream>
#include <stdlib.h>

#include "FileReader.hpp"
#include "Interpreter.hpp"



void doFile(int num);
bool checkInput(std::string& input);

int main()
{
    
    
    std::string input;
    std::cout<<"Choose what file to interpret:\n0: Current\n1: E.java\n2: D1.java\n3: D2.java\n4: D3.java\n5: C1.java\n6: C2.java\n7: B.java\n8: A.java\nPresse anyting else to exit\n";
    while(checkInput(input))
    {
      std::cout<<"\nOutput:\n";
      doFile(std::stoi(input));
      std::cout<<"Press any Enter to continue";
      std::cin.ignore();
      std::cin.get();
      system("clear");
      std::cout<<"Choose what file to interpret:\n0: Current\n1: E.java\n2: D1.java\n3: D2.java\n4: D3.java\n5: C1.java\n6: C2.java\n7: B.java\n8: A.java\nPresse anyting else to exit\n";
    }

    return 0;
}

bool checkInput(std::string& input)
{
  
  std::cin>>input;
  if(input == "0"
  ||input == "1"
  ||input == "2"
  ||input == "3"
  ||input == "4"
  ||input == "5"
  ||input == "6"
  ||input == "7"
  ||input == "8")
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
  case 2:
    name = "test_bytecode/D1.txt";
    break;
  case 3:
    name = "test_bytecode/D2.txt";
    break;
  case 4:
    name = "test_bytecode/D3.txt";
    break;
  case 5:
    name = "test_bytecode/C1.txt";
    break;
  case 6:
    name = "test_bytecode/C2.txt";
    break;
  case 7:
    name = "test_bytecode/B.txt";
    break;
  case 8:
    name = "test_bytecode/A.txt";
    break;
  default:
    name = "byte_code.txt";
    break;
  }
  FileReader fr;
  ByteCodeProgram* prog = fr.ReadFile(name);
  //fr.printProgram(prog);
  Interpreter ir(prog);
  ir.execute();
}