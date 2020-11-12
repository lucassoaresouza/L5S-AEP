#ifndef FIELD_H
#define FIELD_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "gameObject.hpp"
#include "game.hpp"
#include "log.hpp"

namespace Engine{
    class Field : public GameObject {
        private:
            SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
            
            TTF_Font *font = NULL;
            std::string font_path;
            SDL_Color color_text = {0x0, 0xF0, 0x0, 0x0};
            SDL_Texture *font_texture = NULL;
            int font_size;
            std::string text;
            bool is_bold = false;

        public:
            Field(
                std::string object_name,
                std::pair<int, int> object_position,
                std::pair<int, int> object_size
            );
            ~Field(){};
            void set_color(Uint64 r, Uint64 g, Uint64 b, Uint64 a);
            void set_font(std::string path, int size);
            void set_text(std::string new_text);
            void set_bold(bool bold);
            bool load();
            void draw();
            void free();

    };
}

#endif