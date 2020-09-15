#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "log.hpp"

namespace Engine{
    class TextField{
        private:
            std::string name = "";
            std::pair<int, int> position;
            std::string current_text = "AbCdEfGhIj";
            int lines = 0;
            int columns = 0;
            SDL_Texture* texture = NULL;
            SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};
            std::string font_path = "";
            int font_size = 0;
            TTF_Font *font = NULL;

        public:
            TextField(
                std::string object_name,
                std::pair<int, int> object_position,
                int max_lines,
                int max_columns
            );
            ~TextField();
            bool load();
            void draw();
            void set_font(std::string path, int size);
            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 alfa);
    };
}

#endif