#ifndef CHALLENGE_MAP_H
#define CHALLENGE_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"
#include "../engine/inc/collider.hpp"
#include "../engine/inc/field.hpp"
#include "../inc/checkableField.hpp"

class ChallengeMap : public Engine::GameObject{
    private:
        std::string map_path;
        std::string map_info;
        std::string text_info;
        std::vector<CheckableField*> tiles;
        int columns = 15;
        int lines = 15;
        int spacing = 1;
        int tile_quad_size = 32;
        std::pair<int, int> possible_positions[15][15];
        bool completed = false;
        std::pair<int, int> obj_initial_position;

        bool load_tiles();
        void draw_tiles();
        void add_background();
        void add_table_border();
        void line_border();
        void column_border();
        void load_map_info();

    public:
        ChallengeMap(
            std::string map_name,
            std::pair<int, int>position,
            std::string info,
            std::string text
        );
        ~ChallengeMap(){};
        void init();
        bool load();
        void draw();
        std::pair<int,int> get_possible_position(int x, int y);
        std::pair<int, int> get_obj_initial_position();
        std::pair<std::pair<int, int>,std::pair<int, int>> get_limits();
        void set_completed(bool status);
        bool get_completed();
        void set_obj_initial_position(int x, int y);
        bool verify_all_trail_checked();
        void reset_all_trail_checks();
};

#endif