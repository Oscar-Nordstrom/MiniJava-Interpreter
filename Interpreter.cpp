#include "Interpreter.hpp"

Activation::Activation(int ic, int ac, ByteCodeMethod *method)
    :instructionCounter(ic), argumentCounter(ac), method(method)
{
    for(auto& v: method->vars)
    {
        this->local_vars.insert({v->id, 0});
    }
}

Bytecode *Activation::getNext()
{
    if(this->instructionCounter >= this->method->instructions.size())
    {
        std::cout<<"Instruction counter too big\n";
        return nullptr;
    }
    if(this->argumentCounter >= this->method->instructions[this->instructionCounter].arguments.size())
    {
        instructionCounter++;
        this->argumentCounter = 0;
    }

    return &this->method->instructions[this->instructionCounter].arguments[this->argumentCounter++];
}

void Activation::gotoInstruction(std::string name)
{
    for(int i = 0; i < this->method->instructions.size(); i++)
    {
        if(this->method->instructions[i].name == name)
        {
            //std::cout<<"Found goto instruction: "<<this->method->instructions[i].name<<std::endl;
            this->instructionCounter = i;
            this->argumentCounter = 0;
            break;
        }
    }
}

Interpreter::Interpreter(ByteCodeProgram *program)
{
    this->program = program;
    this->mainMethod = this->getMain();
}

ByteCodeMethod *Interpreter::getMain()
{
    ByteCodeMethod* ret = nullptr;
    for(auto& m: this->program->methodsVec)
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

void Interpreter::execute()
{  
    ByteCodeMethod* m = this->mainMethod;
    Activation* current_activation = new Activation(0, 0, m);
    Bytecode* curInstruction = new Bytecode();
    std::stack<Activation*> activationStack;
    int one, two;
    while(curInstruction->type != InstructionType::stop)
    {
        curInstruction = current_activation->getNext();
        //std::cout<<curInstruction->getString()<<std::endl;
        switch (curInstruction->type)
        {
        case InstructionType::iload: 
            //std::cout<<"iload: "<<curInstruction->what<<std::endl;
            this->dataStack.push(current_activation->local_vars.at(curInstruction->what));
            //std::cout<<"iload: "<<curInstruction->what<<": "<<this->dataStack.top()<<std::endl;
            break;
        case InstructionType::iconst: 
            this->dataStack.push(this->getWhat(curInstruction->what));
            //std::cout<<"iconst: "<<curInstruction->what<<": "<<this->dataStack.top()<<std::endl;
            break;
        case InstructionType::istore: 
            //std::cout<<"istore: "<<curInstruction->what<<std::endl;
            one = this->dataStack.top();
            this->dataStack.pop();
            current_activation->local_vars.at(curInstruction->what) = one;
            //std::cout<<"istore: "<<curInstruction->what<<": "<<one<<std::endl;
            break;
        case InstructionType::iadd: 
            this->handleArgumentOp(InstructionType::iadd);
            break;
        case InstructionType::isub: 
            this->handleArgumentOp(InstructionType::isub);
            break;
        case InstructionType::imul: 
            this->handleArgumentOp(InstructionType::imul);
            break;
        case InstructionType::idiv: 
            this->handleArgumentOp(InstructionType::idiv);
            break;
        case InstructionType::ilt: 
            this->handleArgumentOp(InstructionType::ilt);
            break;
        case InstructionType::igt: 
            this->handleArgumentOp(InstructionType::igt);
            break;
        case InstructionType::ieq: 
            this->handleArgumentOp(InstructionType::ieq);
            break;
        case InstructionType::iand: 
            this->handleArgumentOp(InstructionType::iand);
            break;
        case InstructionType::ior: 
            this->handleArgumentOp(InstructionType::ior);
            break;
        case InstructionType::inot: 
            one = this->dataStack.top();
            this->dataStack.pop();
            if(one == 0)
                this->dataStack.push(1);
            else
                this->dataStack.push(0);
            break;
        case InstructionType::goto_i: 
            //std::cout<<"goto: "<<curInstruction->getString()<<std::endl;
            current_activation->gotoInstruction(curInstruction->what);
            break;
        case InstructionType::iffalse_goto_i: 
            //std::cout<<"if: "<<curInstruction->getString()<<std::endl;
            one = this->dataStack.top();
            this->dataStack.pop();
            if(one == 0)
            {     
                current_activation->gotoInstruction(curInstruction->what);
            }
            break;
        case InstructionType::invokevirtual_m: 
            activationStack.push(current_activation);
            current_activation = new Activation(0,0, this->getMethod(curInstruction->what));
            //std::cout<<"invokevirtual_m: "<<curInstruction->what<<std::endl;
            break;
        case InstructionType::ireturn: 
            current_activation = activationStack.top();
            activationStack.pop();
            break;
        case InstructionType::print: 
            one = this->dataStack.top();
            this->dataStack.pop();
            std::cout<<one<<std::endl;
            break;
        }
    }
}

void Interpreter::handleArgumentOp(InstructionType instruction)
{
    int v1 = this->dataStack.top();
    this->dataStack.pop();
    int v2 = this->dataStack.top();
    this->dataStack.pop();

    switch (instruction)
    {
    case InstructionType::iadd:
        this->dataStack.push(v2+v1);
        //std::cout<<"Adding: "<<v1<<"+"<<v2<<"="<<this->dataStack.top()<<std::endl;
        break;
    case InstructionType::isub:
        this->dataStack.push(v2-v1);
        //std::cout<<"Subing: "<<v2<<"-"<<v1<<"="<<this->dataStack.top()<<std::endl;
        break;
    case InstructionType::imul:
        this->dataStack.push(v2*v1);
        //std::cout<<"Multing: "<<v2<<"*"<<v1<<"="<<this->dataStack.top()<<std::endl;
        break;
    case InstructionType::idiv:
        this->dataStack.push(v2/v1);
        break;
    case InstructionType::ilt:
        if(v2 < v1)
            this->dataStack.push(1);     
        else
            this->dataStack.push(0);     
        break;
    case InstructionType::igt:
        if(v2 > v1)
            this->dataStack.push(1);
        else    
            this->dataStack.push(0);
        break;
    case InstructionType::ieq:
        if(v2 == v1)
            this->dataStack.push(1);
        else    
            this->dataStack.push(0);
        break;
    case InstructionType::iand:
        if(v1*v2 == 0)
            this->dataStack.push(0);
        else    
            this->dataStack.push(1);
        break;
    case InstructionType::ior:
        if(v1+v2 == 0)
            this->dataStack.push(0);
        else    
            this->dataStack.push(1);
        break;
    }
}

int Interpreter::getWhat(std::string what)
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

ByteCodeMethod *Interpreter::getMethod(std::string name)
{
    ByteCodeMethod* ret = this->program->methods[name];
    if(ret == nullptr)
    {
        std::cout<<"Could not find method: "<<name<<std::endl;
    }
    else
    {
        //std::cout<<"found method: "<<ret->getData()<<std::endl;
    }
    return ret;
}
