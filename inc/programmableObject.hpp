#ifndef PROGRAMMABLE_OBJECT_H
#define PROGRAMMABLE_OBJECT_H

#include <vector>
#include <iostream>
#include <string>

#include "../compiler/command.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"

class ProgrammableObject : public Engine::GameObject{
    private:
        std::vector<Compiler::Command> commands;
        int direction_angle;
    
    public:
        ProgrammableObject(
            std::string object_name,
            std::pair<int, int> object_position,
            std::pair<int, int> object_size
        );
        ~ProgrammableObject();
        void draw();
        void add_commands(std::vector<Compiler::Command>& new_commands);
        void set_direction(std::string new_direction);
        int get_direction();
        void read_input(SDL_Event *event);
};

#endif