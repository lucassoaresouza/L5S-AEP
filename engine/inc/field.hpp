#ifndef FIELD_H
#define FIELD_H

#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "game.hpp"
#include "gameObject.hpp"
#include "log.hpp"

namespace Engine {
class Field : public GameObject {
 protected:
  TTF_Font* font = NULL;
  std::string text[10];
  SDL_Texture* font_texture[10];
  SDL_Rect text_quads[10];
  int font_size;
  SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};
  SDL_Color color_text = {0x0, 0xF0, 0x0, 0x0};
  std::string font_path;
  bool is_bold = false;
  int rotation = 0;
  void draw_texts();

 public:
  Field() {};
  Field(std::string object_name, std::pair<int, int> object_position,
        std::pair<int, int> object_size);
  ~Field() {};
  void set_color(Uint64 r, Uint64 g, Uint64 b, Uint64 a);
  void set_font(std::string path, int size);
  void set_text_per_line(std::string new_text, int line);
  void set_bold(bool bold);
  void set_sprite(std::string path, std::string orientation);
  bool load();
  void draw();
  void free();
};
}  // namespace Engine

#endif