#ifndef FIELD_H
#define FIELD_H

#include <SDL2/SDL.h>
#include <iostream>

#include "gameObject.hpp"
#include "game.hpp"
#include "log.hpp"

namespace Engine{
    class Field : public GameObject {
        private:
            SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};

        public:
            Field(
                std::string object_name,
                std::pair<int, int> object_position,
                std::pair<int, int> object_size
            );
            ~Field(){};
            void set_color(Uint64 r, Uint64 g, Uint64 b, Uint64 a);
            bool load();
            void draw();

    };
}

#endif