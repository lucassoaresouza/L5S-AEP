#include "../inc/timer.hpp"

using namespace Engine;

Timer::Timer() {
  start_ticks = 0;
  paused_ticks = 0;
  paused = false;
  started = false;
}

void Timer::start() {
  started = true;
  paused = false;
  start_ticks = SDL_GetTicks();
  paused_ticks = 0;
}

void Timer::stop() {
  started = false;
  paused = false;
  start_ticks = 0;
  paused_ticks = 0;
}

void Timer::pause() {
  if (started && !paused) {
    paused = true;
    paused_ticks = SDL_GetTicks() - start_ticks;
    start_ticks = 0;
  }
}

Uint32 Timer::get_ticks() {
  Uint32 time = 0;
  if (started) {
    if (paused) {
      time = paused_ticks;
    } else {
      time = SDL_GetTicks() - start_ticks;
    }
  }
  return time;
}

bool Timer::is_started() { return started; }

bool Timer::is_paused() { return paused; }