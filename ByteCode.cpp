#include "ByteCode.hpp"
ByteCode::ByteCode()
    :type(InstructionType::nothing), what("")
{
}

ByteCode::ByteCode(InstructionType type, std::string what)
    :type(type), what(what)
{
}

std::string ByteCode::getString()
{
    std::string ret = "";
    switch (this->type)
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
    ret = ret + " " + this->what;
    return ret;
}




ByteCodeProgram::ByteCodeProgram()
{
}

void ByteCodeProgram::setData(std::string data)
{
    this->data = data;
}

std::string ByteCodeProgram::getData()
{
    return this->data;
}

ByteCodeMethod::ByteCodeMethod()
{
}

void ByteCodeMethod::setData(std::string data)
{
    this->data = data;
}

std::string ByteCodeMethod::getData()
{
    return this->data;
}

ByteCodeInstruction::ByteCodeInstruction()
{
}

void ByteCodeInstruction::setData(std::string data)
{
    this->data = data;
}

std::string ByteCodeInstruction::getData()
{
    return this->data;
}
