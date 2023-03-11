#include "StackMachine.hpp"

StackMachine::StackMachine()
{
}

void StackMachine::interprete(ByteCodeProgram *program)
{
    std::stack<int> theStack;
    std::unordered_map<std::string, int> localVars;
    ByteCodeMethod* mainMethod = this->getMain(program);

    for(auto v: mainMethod->vars)
    {
        localVars.insert({v->getID(), 0});
    }
    
    for(auto i: mainMethod->instructions)
    {
        this->handleInstruction(&theStack, &localVars, mainMethod, &i);
    }
}

ByteCodeMethod* StackMachine::getMain(ByteCodeProgram *program)
{
    ByteCodeMethod* ret = nullptr;
    for(auto& m: program->methodsVec)
    {
        if(m.data.find("main")!=std::string::npos)
        {
            ret = &m;
            break;
        }
    }
    if(ret == nullptr)
    {
        std::cout<<"Did not find main function.\n";
    }
    return ret;
}

Variable *StackMachine::getVar(ByteCodeMethod *method, std::string var)
{
    Variable* ret = nullptr;
    for(auto v: method->vars)
    {
        if(var == v->getID())
        {
            ret = v;
        }
    }
    if(ret == nullptr)
    {
        std::cout<<"Did not find variable.\n";
    }
    return ret;
}

void StackMachine::handleInstruction(std::stack<int> *theStack, std::unordered_map<std::string, int>* localVars, ByteCodeMethod *method, ByteCodeInstruction *instruction)
{
    for(auto a: instruction->arguments)
    {
        this->handleArgument(theStack, localVars, method, instruction, &a);
    }
}

void StackMachine::handleArgument(std::stack<int> *theStack, std::unordered_map<std::string, int>* localVars, ByteCodeMethod *method, ByteCodeInstruction *instruction, ByteCode *argument)
{
    int one, two;
    switch (argument->type)
    {
    case InstructionType::iload: 
        theStack->push(localVars->at(argument->what));
        //std::cout<<"Loaded: "<<argument->what<<": "<<localVars->at(argument->what)<<" : "<<theStack->top()<<std::endl;
        break;
    case InstructionType::iconst: 
        theStack->push(this->getWhat(argument->what));
        break;
    case InstructionType::istore: 
        one = theStack->top();
        theStack->pop();
        localVars->at(argument->what) = one;
        break;
    case InstructionType::iadd: 
        this->handleArgumentOp(theStack, InstructionType::iadd);
        break;
    case InstructionType::isub: 
        this->handleArgumentOp(theStack, InstructionType::isub);
        break;
    case InstructionType::imul: 
        this->handleArgumentOp(theStack, InstructionType::imul);
        break;
    case InstructionType::idiv: 
        this->handleArgumentOp(theStack, InstructionType::idiv);
        break;
    case InstructionType::ilt: 
        this->handleArgumentOp(theStack, InstructionType::ilt);
        break;
    case InstructionType::igt: 
        this->handleArgumentOp(theStack, InstructionType::igt);
        break;
    case InstructionType::ieq: 
        this->handleArgumentOp(theStack, InstructionType::ieq);
        break;
    case InstructionType::iand: 
        this->handleArgumentOp(theStack, InstructionType::iand);
        break;
    case InstructionType::ior: 
        this->handleArgumentOp(theStack, InstructionType::ior);
        break;
    case InstructionType::inot: 
        one = theStack->top();
        theStack->pop();
        if(one == 0)
            theStack->push(1);
        else
            theStack->push(0);
        break;
    case InstructionType::goto_i: 
        
        break;
    case InstructionType::iffalse_goto_i: 
        
        break;
    case InstructionType::invokevirtual_m: 
        
        break;
    case InstructionType::ireturn: 
        
        break;
    case InstructionType::print: 
        one = theStack->top();
        theStack->pop();
        std::cout<<one<<std::endl;
        break;
    case InstructionType::stop: 
        return;
        break;
    case InstructionType::nothing: 
        
        break;
    }
}

int StackMachine::getWhat(std::string what)
{
    int ret = -1;
    if(what == "true")
    {
        ret = 1;
    }
    else if(what == "false")
    {
        ret = 0;
    }
    else
    {
        ret = std::stoi(what);
    }
    return ret;
}

void StackMachine::handleArgumentOp(std::stack<int> *theStack, InstructionType type)
{
    int v1 = theStack->top();
    theStack->pop();
    int v2 = theStack->top();
    theStack->pop();

    switch (type)
    {
    case InstructionType::iadd:
        theStack->push(v2+v1);
        //std::cout<<"Adding: "<<v1<<"+"<<v2<<"="<<theStack->top()<<std::endl;
        break;
    case InstructionType::isub:
        theStack->push(v2-v1);
        //std::cout<<"Subing: "<<v2<<"-"<<v1<<"="<<theStack->top()<<std::endl;
        break;
    case InstructionType::imul:
        theStack->push(v2*v1);
        //std::cout<<"Multing: "<<v2<<"*"<<v1<<"="<<theStack->top()<<std::endl;
        break;
    case InstructionType::idiv:
        theStack->push(v2/v1);
        break;
    case InstructionType::ilt:
        if(v2 < v1)
            theStack->push(1);
        else    
            theStack->push(0);
        break;
    case InstructionType::igt:
        if(v2 > v1)
            theStack->push(1);
        else    
            theStack->push(0);
        break;
    case InstructionType::ieq:
        if(v2 == v1)
            theStack->push(1);
        else    
            theStack->push(0);
        break;
    case InstructionType::iand:
        if(v1*v2 == 0)
            theStack->push(0);
        else    
            theStack->push(1);
        break;
    case InstructionType::ior:
        if(v1+v2 == 0)
            theStack->push(0);
        else    
            theStack->push(1);
        break;
    }
}

std::string StackMachine::getTypeString(InstructionType type)
{
     std::string ret = "";
    switch (type)
    {
    case InstructionType::iload: 
        ret = "iload";
        break;
    case InstructionType::iconst: 
        ret = "iconst";
        break;
    case InstructionType::istore: 
        ret = "istore";
        break;
    case InstructionType::iadd: 
        ret = "iadd";
        break;
    case InstructionType::isub: 
        ret = "isub";
        break;
    case InstructionType::imul: 
        ret = "imul";
        break;
    case InstructionType::idiv: 
        ret = "idiv";
        break;
    case InstructionType::ilt: 
        ret = "ilt";
        break;
    case InstructionType::igt: 
        ret = "igt";
        break;
    case InstructionType::ieq: 
        ret = "ieq";
        break;
    case InstructionType::iand: 
        ret = "iand";
        break;
    case InstructionType::ior: 
        ret = "ior";
        break;
    case InstructionType::inot: 
        ret = "inot";
        break;
    case InstructionType::goto_i: 
        ret = "goto_i";
        break;
    case InstructionType::iffalse_goto_i: 
        ret = "iffalse_goto_i";
        break;
    case InstructionType::invokevirtual_m: 
        ret = "invokevirtual_m";
        break;
    case InstructionType::ireturn: 
        ret = "ireturn";
        break;
    case InstructionType::print: 
        ret = "print";
        break;
    case InstructionType::stop: 
        ret = "stop";
        break;
    case InstructionType::nothing: 
        ret = "nothing";
        break;
    }
    return ret;
}

InstructionType StackMachine::getStringType(std::string type)
{
        InstructionType ret = InstructionType::nothing;
    if(type == "iload")
    {
        ret = InstructionType::iload;
    }
    else if(type == "")
    {
        ret = InstructionType::iconst;
    }
    else if(type == "istore")
    {
        ret = InstructionType::istore;
    }
    else if(type == "iadd")
    {
        ret = InstructionType::iadd;
    }
    else if(type == "isub")
    {
        ret = InstructionType::isub;
    }
    else if(type == "imul")
    {
        ret = InstructionType::imul;
    }
    else if(type == "idiv")
    {
        ret = InstructionType::idiv;
    }
    else if(type == "ilt")
    {
        ret = InstructionType::ilt;
    }
    else if(type == "igt")
    {
        ret = InstructionType::igt;
    }
    else if(type == "ieq")
    {
        ret = InstructionType::ieq;
    }
    else if(type == "iand")
    {
        ret = InstructionType::iand;
    }
    else if(type == "ior")
    {
        ret = InstructionType::ior;
    }
    else if(type == "inot")
    {
        ret = InstructionType::inot;
    }
    else if(type == "goto_i")
    {
        ret = InstructionType::goto_i;
    }
    else if(type == "iffalse_goto_i")
    {
        ret = InstructionType::iffalse_goto_i;
    }
    else if(type == "invokevirtual_m")
    {
        ret = InstructionType::invokevirtual_m;
    }
    else if(type == "ireturn")
    {
        ret = InstructionType::ireturn;
    }
    else if(type == "print")
    {
        ret = InstructionType::print;
    }
    else if(type == "stop")
    {
        ret = InstructionType::stop;
    }

    return ret;
}
