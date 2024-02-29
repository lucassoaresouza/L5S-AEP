#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "log.hpp"

namespace Engine {
class GameObject {
 private:
  std::string name = "";
  bool listening_inputs = false;

 protected:
  std::string sprite = "";
  std::pair<int, int> position;
  std::pair<int, int> size;
  SDL_Texture* texture = NULL;

 public:
  GameObject();
  GameObject(std::string object_name, std::pair<int, int> object_position,
             std::pair<int, int> object_size);
  ~GameObject() {};
  void set_position(std::pair<int, int> object_position);
  void set_name(std::string object_name);
  void set_size(std::pair<int, int> object_size);
  void set_sprite(std::string path);
  void set_texture(SDL_Texture* new_texture);

  std::pair<int, int> get_position();
  int get_position_x();
  int get_position_y();
  std::string get_sprite();

  std::pair<int, int> get_size();
  std::string get_name();
  int get_width();
  int get_height();

  virtual bool load();
  virtual void free();
  virtual void draw();
  virtual void read_input(SDL_Event* event);
  virtual void collide() {};
};
}  // namespace Engine

#endif