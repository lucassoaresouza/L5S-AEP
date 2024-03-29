#ifndef SELECTOR_H
#define SELECTOR_H

#include <iostream>
#include <vector>

#include "../engine/inc/collider.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/gameObject.hpp"

class Selector : public Engine::GameObject {
 private:
  std::vector<std::pair<int, int>> possible_positions;
  int lines;
  int columns;
  int displacement;
  std::pair<int, int> limit_x;
  std::pair<int, int> limit_y;
  std::string selected_sprite;

 public:
  Selector(std::string name, std::pair<int, int> position,
           std::pair<int, int> size, int count_lines, int count_columns,
           int count_displacement);
  ~Selector() {};
  void add_position(std::pair<int, int> position);
  void set_new_position_mouse(int x, int y);
  void read_input(SDL_Event *event);
  void verify_collisions();
  std::string get_selected_sprite();
};

#endif