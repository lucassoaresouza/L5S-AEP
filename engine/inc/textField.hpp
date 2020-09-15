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
            std::string current_text = "";
            int lines = 0;
            int columns = 0;
            std::string **text_table;
            SDL_Texture *background;
            SDL_Texture ***texture_table;
            std::pair<int, int> pointer_position;
            int spacing_line = 0;
            int spacing_letter = 0;

            SDL_Texture* texture = NULL;
            SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};
            SDL_Color background_color = {0xFF, 0xFF, 0xFF, 0xFF};
            std::string font_path = "";
            int font_size = 0;
            TTF_Font *font = NULL;

            void allocate_tables();
            void read_input();

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
            void free();
            void set_font(std::string path, int size);
            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 alfa);
            void write(char letter);
            void set_spacing_line(int spacing);
            void set_spacing_letter(int spacing);
            std::string get_current_text();
    };
}

#endif