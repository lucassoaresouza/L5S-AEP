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
        int columns = 0;
        int lines = 0;
        int spacing = 0;

        bool read_file();
        bool load_tiles();
        void draw_tiles();

    public:
        ChallengeMap(
            std::string map_name,
            std::pair<int, int>position,
            std::string path
        );
        ~ChallengeMap(){};
        void add_background(int columns, int lines, int spacing);
        bool load();
        void draw();
};

#endif