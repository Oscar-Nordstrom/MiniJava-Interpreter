#include "FileReader.hpp"

FileReader::FileReader()
{
}

ByteCodeProgram *FileReader::ReadFile(std::string fileName)
{
    std::ifstream file(fileName);
    if(!file.is_open())
    {
        std::cout<<"Could not open file: "<<fileName<<"\n";
        return nullptr;
    }

    ByteCodeProgram* program = new ByteCodeProgram();

    int numMethods;
    file>>numMethods;
    //std::cout<<"Number of methods: "<<numMethods<<std::endl;
    program->methodsVec.resize(numMethods);

    for(int i = 0; i < numMethods; i++)
    {
        ByteCodeMethod& curMeth = program->methodsVec[i];
        std::string methodName;
        file>>methodName;
        //std::cout<<"Method "<<methodName<<std::endl;
        curMeth.setData(methodName);
        program->methods.insert({methodName, &curMeth});
        int numVars;
        file>>numVars;
        //std::cout<<"NumVars: "<<numVars<<std::endl;
        curMeth.vars.resize(numVars);
        for(int j = 0; j < numVars; j++)
        {
            std::string varType;
            std::string varID;

            file>>varType;
            file>>varID;

            //std::cout<<"Var: type: "<<varType<<" ID: "<<varID<<std::endl;
            curMeth.vars[j] = new Variable(varID, varType);
        }

        int numInstructions;
        file>>numInstructions;
        //std::cout<<"NumInstructions: "<<numInstructions<<std::endl;
        curMeth.instructions.resize(numInstructions);
        for(int i = 0; i < numInstructions; i++)
        {
            std::string instructionName;
            file>>instructionName;
            //std::cout<<"Instruction: "<<instructionName<<std::endl;
            curMeth.instructions[i].name = instructionName;

            int numArguments;
            file>>numArguments;
            //std::cout<<"NumArguments: "<<numArguments<<std::endl;
            curMeth.instructions[i].arguments.resize(numArguments);
            for(int j = 0; j < numArguments; j++)
            {
                std::string argument = "";
                std::string argumentType = "";
                file>>argumentType;
                if(argumentType != getTypeString(InstructionType::print)
                    &&argumentType != getTypeString(InstructionType::inot)
                    &&argumentType != getTypeString(InstructionType::stop)
                    &&argumentType != getTypeString(InstructionType::ireturn))
                {
                    file>>argument;
                }
                
                //std::cout<<"Argument: "<<argumentType<<" "<<argument<<std::endl;
                curMeth.instructions[i].arguments[j].type = getStringType(argumentType);
                curMeth.instructions[i].arguments[j].what = argument;
            }
        }

        
    }

    file.close();

    return program;
}

void FileReader::printProgram(ByteCodeProgram *program)
{
    for(auto m: program->methodsVec)
    {
        std::cout<<m.data<<"\n";
        for(auto v: m.vars)
        {
            std::cout<<v->id<<std::endl;
        }
        for(auto i: m.instructions)
        {
            std::cout<<"\t"<<i.name<<std::endl;
            for(auto a: i.arguments)
            {
                std::cout<<"\t\t"<<a.getString()<<std::endl;
            }
        }
    }
}

std::string FileReader::getTypeString(InstructionType type)
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

InstructionType FileReader::getStringType(std::string type)
{
    InstructionType ret = InstructionType::nothing;
    if(type == "iload")
    {
        ret = InstructionType::iload;
    }
    else if(type == "iconst")
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
