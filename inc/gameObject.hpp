#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class GameObject {

    private:
        std::pair<int, int> position;
        std::string name = "";
        std::pair<int, int> size;

    public:
        GameObject();
        GameObject(
            std::string object_name,
            std::pair<int, int> object_position
        );
        ~GameObject(){};
        void set_position(std::pair <int, int> object_position);
        void set_name(std::string object_name);
        void set_size(std::pair<int, int> object_size);

        std::pair<int, int> get_position();
        int get_position_x();
        int get_position_y();

        std::pair<int, int> get_size();
        int get_width();
        int get_height();

};

#endif