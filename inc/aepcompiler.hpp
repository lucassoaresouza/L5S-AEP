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
        Compiler::Interpreter interpreter;

    public:
        AEPCompiler(){};
        ~AEPCompiler(){};
        std::vector<std::pair<std::string, double>> run(std::string);
        void clear();

};

#endif