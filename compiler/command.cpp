#include "command.hpp"

#include <iostream>
#include <sstream>

using namespace Compiler;
using std::cout;
using std::endl;

Command::Command(const std::string &name, const std::vector<uint64_t> arguments){
    m_name = name;
    m_args = arguments;
}

Command::Command(const std::string &name){
    m_name = name;
}

Command::Command() :
    m_name(),
    m_args()
{}

Command::~Command(){}

std::string Command::str() const {
    cout << "Command name: " << m_name << endl;
    return m_name;
}

std::string Command::name() const {
    return m_name;
}