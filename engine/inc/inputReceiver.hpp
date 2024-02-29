#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <vector>

#include "gameObject.hpp"
#include "textField.hpp"

namespace Engine {
class InputReceiver {
 private:
  static InputReceiver* instance;
  SDL_Event last_event;
  InputReceiver() {};
  std::string text;
  std::vector<GameObject*> observers;

 public:
  static InputReceiver& get_instance();
  void run();
  SDL_Event* get_last_input();
  void register_observer(GameObject* observer);
  void unregister_observer(std::string name);
  void notify_observers(SDL_Event* event);
  void clear_observers();
};
}  // namespace Engine

#endif