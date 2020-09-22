#ifndef PROGRAMMABLE_OBJECT_H
#define PROGRAMMABLE_OBJECT_H

#include <vector>
#include <iostream>
#include <string>

#include "../compiler/command.hpp"
#include "../engine/inc/gameObject.hpp"

class ProgrammableObject : public Engine::GameObject{
    private:
        std::vector<Compiler::Command> commands;
    
    public:
        ProgrammableObject(
            std::string object_name,
            std::pair<int, int> object_position,
            std::pair<int, int> object_size
        );
        ~ProgrammableObject();
        void add_commands(std::vector<Compiler::Command>& new_commands);
};

#endif