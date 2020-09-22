#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "game.hpp"
#include "gameObject.hpp"

namespace Engine{
    class Button : public GameObject {
        private:
            bool is_active = false;
            bool pressed = false;
            SDL_Texture* not_pressed_texture = NULL;
            SDL_Texture* pressed_texture = NULL;
            std::string pressed_sprite;

        public:
            Button(){};
            Button(
                std::string object_name,
                std::pair<int,int>object_position,
                std::pair<int,int>object_size
            );
            ~Button(){};
            virtual void activate();
            virtual void deactivate();
            virtual void execute(){};
            bool was_pressed(int x, int y);
            void read_input(SDL_Event *event);
            // void draw();
            bool load();
            void set_sprites(
                std::string sprite_not_pressed,
                std::string sprite_pressed
            );
    };
}

#endif