#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>
#include <vector>

#include "gameObject.hpp"
#include "log.hpp"
#include "screen.hpp"
#include "screenManage.hpp"
#include "textField.hpp"
#include "timer.hpp"

namespace Engine {
class Game {
 private:
  static Game* instance;
  std::string name;
  std::pair<int, int> window_dimensions;
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  SDL_Texture* game_background = NULL;
  InputReceiver& input_receiver = InputReceiver::get_instance();
  ScreenManage* screen_manager = NULL;
  Screen* actual_screen = NULL;
  Timer* timer;
  Timer* cap_fps_timer;
  int cap_fps = 1000 / 60;
  int frames_count = 0;
  double fps = 0;
  bool quit = false;

  Game() {};
  bool init();
  void set_information(std::string, std::pair<int, int>);
  void draw_background();
  void calculate_fps();
  void cap_max_fps();

 public:
  ~Game() {};
  static Game& get_instance();
  static Game& initialize(std::string, std::pair<int, int>);
  void run();
  void close();

  std::string get_name();
  std::pair<int, int> get_window_dimensions();
  SDL_Renderer* get_renderer();

  void set_window_dimensions(std::pair<int, int> dimensions);
  void set_name(std::string game_name);
  void set_game_background(std::string path);

  void add_screen(Screen* screen);
  void load_screen(std::string screen_name);
  bool search_screen(std::string screen_name);
  void draw_screen();
  void read_input();
};
}  // namespace Engine

#endif