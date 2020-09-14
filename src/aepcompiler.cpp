#include <iostream>
#include <sstream>
#include <string>

#include "aepcompiler.hpp"
#include "../engine/inc/log.hpp"

void AEPCompiler::run(std::string text){
    stringstream* input_string = new std::stringstream(text);
    interpreter.switchInputStream(input_string);
    int response = interpreter.parse();
    Engine::Log().print("Parser finalizado!");
}
