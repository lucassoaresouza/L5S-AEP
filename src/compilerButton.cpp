#include "../inc/compilerButton.hpp"

CompilerButton::CompilerButton(std::string object_name,
                               std::pair<int, int> object_position,
                               std::pair<int, int> object_size) {
  set_name(object_name);
  set_position(object_position);
  set_size(object_size);
}

void CompilerButton::set_programmable(ProgrammableObject* object_programmable) {
  programmable = object_programmable;
}

void CompilerButton::set_compiler(AEPCompiler* aep_compiler) {
  compiler = aep_compiler;
}

void CompilerButton::set_text_field(Engine::TextField* field) {
  text_field = field;
}

void CompilerButton::execute() {
  std::string program;
  program = text_field->get_current_text() + "\n";
  programmable->add_commands(compiler->run(program));
  programmable->run_commands();
  compiler->clear();
}
