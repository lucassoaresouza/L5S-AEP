#ifndef CHALLENGE_MAP_H
#define CHALLENGE_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "../engine/inc/field.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"

class ChallengeMap : public Engine::GameObject{
    private:
        std::string map_path;
        std::vector<Engine::Field*> tiles;
        int columns = 15;
        int lines = 15;
        int spacing = 1;
        int tile_quad_size = 32;
        std::pair<int, int> possible_positions[15][15];

        bool read_file();
        bool load_tiles();
        void draw_tiles();
        void add_background();
        void add_table_border();
        void line_border();
        void column_border();

    public:
        ChallengeMap(
            std::string map_name,
            std::pair<int, int>position,
            std::string path
        );
        ~ChallengeMap(){};
        bool load();
        void draw();
        std::pair<int,int> get_possible_position(int x, int y){
            return possible_positions[x][y];
        }
};

#endif