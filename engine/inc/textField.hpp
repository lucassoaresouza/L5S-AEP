#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>
#include <vector>

#include "gameObject.hpp"
#include "log.hpp"

namespace Engine {
class TextField : public GameObject {
 private:
  std::string name = "";
  std::pair<int, int> position;
  std::string current_text = "";
  int lines = 0;
  int columns = 0;
  SDL_Texture *background;
  int spacing_line = 0;
  int spacing_letter = 0;
  SDL_Renderer *renderer;

  std::vector<std::string> texts;
  std::vector<SDL_Texture *> texts_textures;
  std::vector<SDL_Rect> texts_rects;
  std::pair<int, int> current_pointer_position = std::make_pair(0, 0);

  std::string pointer_pipe = "|";
  SDL_Texture *pointer_texture;

  SDL_Color font_color = {0xFF, 0xFF, 0xFF, 0xFF};
  SDL_Color background_color = {0xFF, 0xFF, 0xFF, 0xFF};
  std::string font_path = "";
  int font_size = 0;
  TTF_Font *font = NULL;

  void draw_pointer_pipe();
  void draw_texts();
  void draw_background();
  void erase();
  void write(char letter);
  void add_endline();
  void move_pointer(std::string code);
  int locate_eol(int line);
  void update_line();

 public:
  TextField(std::string object_name, std::pair<int, int> object_position,
            int max_lines, int max_columns);
  ~TextField() {};
  bool load();
  void draw();
  void free();
  void set_font(std::string path, int size);
  void set_font_color(Uint8 r, Uint8 g, Uint8 b, Uint8 alfa);
  void set_spacing_line(int spacing);
  void set_spacing_letter(int spacing);
  void read_input(SDL_Event *event);
  std::string get_current_text();
};
}  // namespace Engine

#endif