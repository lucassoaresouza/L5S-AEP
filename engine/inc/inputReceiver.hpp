#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <vector>

#include "gameObject.hpp"

namespace Engine{
    class InputReceiver{
        private:
            static InputReceiver* instance;
            SDL_Event event;
            InputReceiver(){};
            std::string text;
            std::vector<GameObject*> observers;

        public:
            static  InputReceiver& get_instance();
            void run();
            SDL_Event* get_last_input();
            void registry_observer(GameObject* observer);
    };
}

#endif