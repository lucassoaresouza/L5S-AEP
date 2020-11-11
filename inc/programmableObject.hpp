#ifndef PROGRAMMABLE_OBJECT_H
#define PROGRAMMABLE_OBJECT_H

#include <vector>
#include <iostream>
#include <string>

#include "../compiler/syntaticTree.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"

class ProgrammableObject : public Engine::GameObject{
    private:
        std::pair<int, int> initial_position;
        command_list commands;
        int direction_angle; // degrees
        std::pair<int, int> orientation; // first = x, second = y
        bool running = false;
        int command_index = 0;
        int expected_x = 0;
        int expected_y = 0;
        void set_initial_state();

    public:
        ProgrammableObject(
            std::string object_name,
            std::pair<int, int> object_position,
            std::pair<int, int> object_size
        );
        ~ProgrammableObject();
        void draw();
        void add_commands(command_list new_commands);
        void run_commands();

        //Basic commands
        void set_direction(std::string new_direction);
        void move(int distance);

        void execute();
};

#endif