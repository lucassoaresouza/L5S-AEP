#include "../inc/programmableObject.hpp"


ProgrammableObject::ProgrammableObject(
    std::string object_name,
    std::pair<int, int> object_position,
    std::pair<int, int> object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
}

void ProgrammableObject::add_commands(
    std::vector<Compiler::Command>& new_commands
){
    commands = new_commands;
}