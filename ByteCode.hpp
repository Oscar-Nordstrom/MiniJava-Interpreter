#pragma once

#include "Variable.hpp"

#include <string>
#include <vector>
#include <unordered_map>

enum class InstructionType
{
    iload,              //Push integer value stored in local variable n.
    iconst,             //Push integer value v.
    istore,             //Pop value v and store it in local variable n.           
    iadd,               //Pop value v1 and v2. Push v2 + v1.   
    isub,               //Pop value v1 and v2. Push v2 - v1.   
    imul,               //Pop value v1 and v2. Push v2 * v1.
    idiv,               //Pop value v1 and v2. Push v2 / v1.   
    ilt,                //Pop value v1 and v2. Push 1 if v2 <v1, else push 0.  
    igt,                //Pop value v1 and v2. Push 1 if v2 >v1, else push 0.   
    ieq,                //Pop value v1 and v2. Push 1 if v2 == v1, else push 0.  
    iand,               //Pop value v1 and v2. Push 0 if v1 * v2 == 0, else push 1.   
    ior,                //Pop value v1 and v2. Push 0 if v1 + v2 == 0, else push 1.
    inot,               //Pop value v. Push 1 if v == 0, else push 0.
    goto_i,             //Jump to instruction labeled i unconditionally.
    iffalse_goto_i,     //Pop value v from the data stack. If v == 0 jump to instruction labeled i, else continue with the following instruction.
    invokevirtual_m,    //Push current activation to the activation stack and switch to the method havingqualified name m.
    ireturn,            //Pop the activation from the activation stack and continue.
    print,              //Pop the value from the data stack and print it.
    stop,               //Execution completed.
    nothing //Default constructor sets this
};

class ByteCode
{
public:
    ByteCode();
    ByteCode(InstructionType type, std::string what = "");
    std::string getString();
    InstructionType type;
    std::string what;
};


class ByteCodeInstruction
{
public:
    ByteCodeInstruction();
    std::string name;
    std::vector<ByteCode> arguments;
    void setData(std::string data);
    std::string getData();
private:
    std::string data;
};
class ByteCodeMethod
{
public:
    ByteCodeMethod();
    std::vector<Variable*> vars;
    std::vector<ByteCodeInstruction> instructions;
    void setData(std::string data);
    std::string getData();
    std::string data;
private:
};
class ByteCodeProgram
{
public:
    ByteCodeProgram();
    std::unordered_map<std::string, ByteCodeMethod*> methods;
    std::vector<ByteCodeMethod> methodsVec;
    void setData(std::string data);
    std::string getData();
private:
    std::string data;
};



