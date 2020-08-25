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
#include "log.hpp"


class Game {

    private:
        static Game* instance;
        std::string name;
        std::pair<int, int> window_dimensions;
        SDL_Window* window =  NULL;
        SDL_Surface* default_surface = NULL;
        std::vector<GameObject*> objects;

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

        void set_window_dimensions(std::pair<int, int>);
        void set_name(std::string);

        void add_object(GameObject* object);
        void load_objects();
        void draw_objects();

};

#endif