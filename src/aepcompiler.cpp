#include <iostream>
#include <sstream>
#include <string>

#include "aepcompiler.hpp"

command_list AEPCompiler::run(std::string text){
    stringstream* input_string = new std::stringstream(text);
    interpreter.switchInputStream(input_string);
    interpreter.parse();
    return interpreter.get_commands();
}

void AEPCompiler::clear(){
    interpreter.clear();
}