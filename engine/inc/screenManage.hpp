#ifndef SCREEN_MANAGE_H
#define SCREEN_MANAGE_H

#include <iostream>
#include <string>
#include <vector>

#include "log.hpp"
#include "screen.hpp"

namespace Engine {
class ScreenManage {
 private:
  std::vector<Screen*> screens;

 public:
  ScreenManage() {};
  void add_screen(Screen* screen);
  Screen* get_screen(std::string screen_name);
  bool search_screen(std::string screen_name);
};
}  // namespace Engine

#endif