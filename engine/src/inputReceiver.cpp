#include "../inc/inputReceiver.hpp"

using namespace Engine;

InputReceiver* InputReceiver::instance = NULL;

InputReceiver& InputReceiver::get_instance() {
  if (!instance) {
    instance = new InputReceiver();
    return *instance;
  } else {
    return *instance;
  }
}

void InputReceiver::run() {
  SDL_Event e;
  SDL_StartTextInput();
  while (SDL_PollEvent(&e) != 0) {
    last_event = e;
    notify_observers(&last_event);
  }
  SDL_StopTextInput();
}

SDL_Event* InputReceiver::get_last_input() { return &last_event; }

void InputReceiver::register_observer(GameObject* observer) {
  observers.push_back(observer);
}

void InputReceiver::unregister_observer(std::string name) {
  int count = 0;
  int observer_position = 0;
  bool result = false;
  for (auto observer : observers) {
    if (observer->get_name() == name) {
      observer_position = count;
      break;
    }
    count += 1;
  }
  observers.erase(observers.begin() + observer_position);
}

void InputReceiver::notify_observers(SDL_Event* event) {
  for (auto observer : observers) {
    observer->read_input(event);
  }
}

void InputReceiver::clear_observers() { observers.clear(); }