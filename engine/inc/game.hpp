#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

#include "gameObject.hpp"
#include "textField.hpp"
#include "log.hpp"

namespace Engine {
    class Game {

        private:
            static Game* instance;
            std::string name;
            std::pair<int, int> window_dimensions;
            std::vector<GameObject*> objects;
            std::vector<TextField*> text_fields;
            SDL_Window* window =  NULL;
            SDL_Renderer* renderer = NULL;
            SDL_Texture* current_texture = NULL;

            Game(){};
            bool init();
            void set_information(std::string, std::pair<int,int>);

        public:
            ~Game(){};
            static Game& get_instance();
            static Game& initialize(std::string, std::pair<int, int>);
            void run();
            void close();
            
            std::string get_name();
            std::pair<int, int> get_window_dimensions();
            SDL_Renderer *get_renderer();

            void set_window_dimensions(std::pair<int, int>);
            void set_name(std::string);

            void add_object(GameObject* object);
            void load_objects();
            void draw_objects();

            void add_textfield(TextField* object);

    };
}

#endif