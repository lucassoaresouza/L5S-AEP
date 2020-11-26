#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

#include "log.hpp"
#include "gameObject.hpp"
#include "inputReceiver.hpp"

namespace Engine {
    class Screen {
        private:
            std::string name;
            InputReceiver& input_receiver = InputReceiver::get_instance();

        protected:
            std::vector<GameObject*> objects;

        public:
            Screen();
            Screen(std::string screen_name);
            ~Screen(){};
            void set_name(std::string screen_name);
            std::string get_name();
            void add_object(GameObject* object);
            void add_object_with_input(GameObject* object);
            void remove_all_objects();
            virtual void init(){};
            virtual void draw();
            virtual void load();
            virtual void free();

    };
}

#endif