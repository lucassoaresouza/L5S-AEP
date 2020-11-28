#ifndef PROGRAMMABLE_OBJECT_H
#define PROGRAMMABLE_OBJECT_H

#include <vector>
#include <iostream>
#include <string>

#include "../compiler/syntaticTree.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"
#include "../engine/inc/collider.hpp"
#include "../engine/inc/field.hpp"
#include "usersManage.hpp"

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
        int move_displacement = 33;
        int pivot_displacement = 33;
        std::pair<
            std::pair<int, int>,
            std::pair<int, int>
        > limits = std::make_pair(
            std::make_pair(0,0),
            std::make_pair(1024,1024)
        );
        std::string status;
        std::pair<int, int> name_displacement = std::make_pair(28,38);

        void set_initial_state();
        bool verify_limits();
        void verify_collisions();

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
        std::string get_status();

        //Basic commands
        void set_initial_position(std::pair<int, int> initial);
        void set_direction(std::string new_direction);
        void move(int distance, int displacement);
        void set_limits(std::pair<int, int> min, std::pair<int,int> max);
        void execute();
};

#endif