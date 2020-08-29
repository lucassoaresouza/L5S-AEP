#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "log.hpp"


namespace Engine{
    class Scene {
        private:
            std::string name="";
            SDL_Surface* surface = NULL;
            bool is_active = false;

        public:
            Scene();
            ~Scene(){};
            virtual void draw();
            virtual void load();
            virtual void free();

            void activate();
            void deactivate();
    };
}

#endif