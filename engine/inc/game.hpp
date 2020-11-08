#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

#include "inputReceiver.hpp"
#include "textField.hpp"
#include "log.hpp"
#include "gameObject.hpp"
#include "screen.hpp"

namespace Engine {
    class Game {

        private:
            static Game* instance;
            std::string name;
            std::pair<int, int> window_dimensions;
            std::vector<GameObject*> objects;
            SDL_Window* window =  NULL;
            SDL_Renderer* renderer = NULL;
            SDL_Texture* current_texture = NULL;
            InputReceiver& input_receiver = InputReceiver::get_instance();

            Game(){};
            bool init();
            void set_information(std::string, std::pair<int,int>);

        public:
            Screen* screen = NULL;
            bool quit = false; //TODO remover essa gambiarra
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
            void read_input();
    };
}

#endif