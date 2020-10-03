#ifndef AEPCOMPILER_H
#define AEPCOMPILER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../compiler/interpreter.hpp"
#include "../compiler/command.hpp"

class AEPCompiler{

    private:
        // static AEPCompiler* instance;
        Compiler::Interpreter interpreter;

    public:
        AEPCompiler(){};
        ~AEPCompiler(){};
        // static AEPCompiler& get_instance();
        std::vector<Compiler::Command> run(std::string);

};

#endif