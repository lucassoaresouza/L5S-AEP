#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "log.hpp"
#include "gameObject.hpp"

namespace Engine{
    class TextField : public GameObject{
        private:
            std::string name = "";
            std::pair<int, int> position;
            std::string current_text = "";
            int lines = 0;
            int columns = 0;
            std::string **text_table;
            SDL_Texture *background;
            SDL_Texture ***texture_table;
            int spacing_line = 0;
            int spacing_letter = 0;
            SDL_Renderer *renderer;

            std::pair<int, int> pointer_position;
            std::string pointer_pipe = "|";
            SDL_Texture *pointer_texture;

            SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};
            SDL_Color background_color = {0xFF, 0xFF, 0xFF, 0xFF};
            std::string font_path = "";
            int font_size = 0;
            TTF_Font *font = NULL;

            void allocate_tables();
            void draw_pointer_pipe();
            void draw_text_table();
            void draw_background();
            void erase();
            void write(char letter);
            void add_endline();
            void move_pointer(std::string code);
            int locate_eol(int line);

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
            void set_font_color(Uint8 r, Uint8 g, Uint8 b, Uint8 alfa);
            void set_spacing_line(int spacing);
            void set_spacing_letter(int spacing);
            void read_input(SDL_Event *event);
            std::string get_current_text();
    };
}

#endif