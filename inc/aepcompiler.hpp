#ifndef AEPCOMPILER_H
#define AEPCOMPILER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../compiler/command.hpp"
#include "../compiler/interpreter.hpp"

class AEPCompiler {
 private:
  Compiler::Interpreter interpreter;

 public:
  AEPCompiler() {};
  ~AEPCompiler() {};
  command_list run(std::string);
  void clear();
};

#endif