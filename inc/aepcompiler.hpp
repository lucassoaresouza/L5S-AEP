#ifndef AEPCOMPILER_H
#define AEPCOMPILER_H

#include <iostream>
#include <sstream>
#include <string>

#include "../compiler/interpreter.hpp"

class AEPCompiler{

    private:
        // static AEPCompiler* instance;
        Compiler::Interpreter interpreter;

    public:
        AEPCompiler(){};
        ~AEPCompiler(){};
        // static AEPCompiler& get_instance();
        void run(std::string);

};

#endif