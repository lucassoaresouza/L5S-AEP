#ifndef CHALLENGE_MAP_H
#define CHALLENGE_MAP_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "../engine/inc/collider.hpp"
#include "../engine/inc/field.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"
#include "../inc/checkableField.hpp"

class ChallengeMap : public Engine::GameObject {
 private:
  std::string map_path;
  std::string map_info;
  std::string text_info;
  std::vector<CheckableField*> tiles;
  int columns = 15;
  int lines = 15;
  int spacing = 1;
  int tile_quad_size = 32;
  std::pair<int, int> possible_positions[15][15];
  bool completed = false;
  std::pair<int, int> obj_initial_position;
  int all_checked_field_count = 0;

  bool load_tiles();
  void draw_tiles();
  void add_background();
  void add_table_border();
  void line_border();
  void column_border();
  void load_map_info();

 public:
  ChallengeMap(std::string map_name, std::pair<int, int> position,
               std::string info, std::string text);
  ~ChallengeMap() {};
  void init();
  bool load();
  void draw();
  void free();
  std::pair<int, int> get_possible_position(int x, int y);
  std::pair<int, int> get_obj_initial_position();
  std::pair<std::pair<int, int>, std::pair<int, int>> get_limits();
  void set_completed(bool status);
  bool get_completed();
  void set_obj_initial_position(int x, int y);
  bool verify_all_trail_checked();
  void reset_all_trail_checks();
  std::string get_text_info();
  int get_all_checked_field_count();
  int get_checked_field_count();
};

#endif