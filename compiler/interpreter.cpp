#include "interpreter.hpp"

#include <sstream>

#include "command.hpp"

using namespace Compiler;

Interpreter::Interpreter()
    : m_scanner(*this),
      m_parser(m_scanner, *this),
      m_location(0),
      manage(new TreeManager()) {}

int Interpreter::parse() {
  m_location = 0;
  return m_parser.parse();
}

void Interpreter::clear() {
  m_location = 0;
  manage->clearNodes();
}

std::string Interpreter::str() const { return "string"; }

void Interpreter::switchInputStream(std::istream* is) {
  m_scanner.switch_streams(is, NULL);
  m_commands.clear();
}

void Interpreter::increaseLocation(unsigned int loc) { m_location += loc; }

unsigned int Interpreter::location() const { return m_location; }

command_list Interpreter::get_commands() {
  manage->run();
  return manage->getCommands();
}

TreeManager* Interpreter::get_manager() { return manage; }
