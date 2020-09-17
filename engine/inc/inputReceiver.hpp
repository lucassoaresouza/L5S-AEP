#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

namespace Engine{
    class InputReceiver{
        private:
            static InputReceiver* instance;
            SDL_Event event;
            InputReceiver(){};
            std::string text;

        public:
            static  InputReceiver& get_instance();
            void run();
            SDL_Event* get_last_input();
    };
}

#endif