#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

namespace Engine{
    class Timer {
        private:
            bool paused;
            bool started;
            Uint32 start_ticks;
            Uint32 paused_ticks;

        public:
            Timer();
            ~Timer(){};
            void start();
            void stop();
            void pause();
            void unpause();
            bool is_paused();
            bool is_started();
            Uint32 get_ticks();
    };
}

#endif