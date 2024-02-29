#include "../inc/textField.hpp"

#include <string>

#include "game.hpp"

using namespace Engine;

TextField::TextField(std::string object_name,
                     std::pair<int, int> object_position, int max_lines,
                     int max_columns) {
  set_name(object_name);
  position = object_position;
  lines = max_lines;
  columns = max_columns;
  for (int i = 0; i < lines; i++) {
    texts.push_back("");
    texts_textures.push_back(NULL);
    texts_rects.push_back({
        0,
        0,
        0,
        0,
    });
  }
}

void TextField::set_font(std::string path, int size) {
  font_path = path;
  font_size = size;
}

void TextField::set_font_color(Uint8 r, Uint8 g, Uint8 b, Uint8 alfa) {
  font_color = {r, g, b, alfa};
}

bool TextField::load() {
  Game& game = Game::get_instance();
  font = TTF_OpenFont(font_path.c_str(), font_size);
  if (font == NULL) {
    Log().print("Houve um problema ao carregar a fonte!");
  }

  for (int i = 0; i < lines; i++) {
    texts.push_back("");
  }

  SDL_Surface* provisory_surface = NULL;
  provisory_surface =
      TTF_RenderText_Blended(font, pointer_pipe.c_str(), font_color);
  pointer_texture =
      SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
  SDL_FreeSurface(provisory_surface);

  return true;
}

void TextField::draw() {
  draw_background();
  draw_pointer_pipe();
  draw_texts();
}

void TextField::draw_texts() {
  Game& game = Game::get_instance();
  int index_line = 0;
  for (std::string line : texts) {
    if (line.size() > 0) {
      SDL_RenderCopy(game.get_renderer(), texts_textures[index_line], NULL,
                     &texts_rects[index_line]);
    }
    index_line++;
  }
}

void TextField::draw_pointer_pipe() {
  Game& game = Game::get_instance();
  SDL_Rect renderQuad = {
      position.first + (9 * current_pointer_position.second) + 7,
      position.second + (18 * current_pointer_position.first) + 15, 9, 18};
  SDL_RenderCopy(game.get_renderer(), pointer_texture, NULL, &renderQuad);
}

void TextField::draw_background() {
  Game& game = Game::get_instance();
  SDL_Rect background_rect = {
      position.first,
      position.second,
      9 * (columns + 3),
      18 * (lines + 2),
  };
  SDL_SetRenderDrawColor(game.get_renderer(), background_color.r,
                         background_color.g, background_color.b,
                         background_color.a);
  SDL_RenderFillRect(game.get_renderer(), &background_rect);
}

void TextField::free() {}

std::string TextField::get_current_text() {
  current_text = "";
  for (std::string line : texts) {
    current_text += line;
  }
  return current_text;
}

void TextField::write(char letter) {
  if (current_pointer_position.first < lines) {
    if (current_pointer_position.second + 1 <= columns) {
      // ok to write
      auto line_it = texts[current_pointer_position.first].begin() +
                     current_pointer_position.second;
      texts[current_pointer_position.first].insert(line_it, letter);
      current_pointer_position.second++;
      update_line();
    } else {
      // got to next line
      if (current_pointer_position.first + 1 < lines) {
        move_pointer("DOWN");
      }
    }
  }
}

void TextField::erase() {
  if (current_pointer_position.second - 1 >= 0) {
    texts[current_pointer_position.first].erase(
        texts[current_pointer_position.first].begin() +
        (current_pointer_position.second - 1));
    current_pointer_position.second--;
    update_line();
  }
}

void TextField::add_endline() {
  write(' ');
  move_pointer("DOWN");
}

void TextField::move_pointer(std::string code) {
  int eol = 0;
  if (code == "UP") {
    if (current_pointer_position.first - 1 >= 0) {
      current_pointer_position.first--;
      eol = texts[current_pointer_position.first].size();
      if (current_pointer_position.second > eol) {
        current_pointer_position.second = eol;
      }
    }
  } else if (code == "LEFT") {
    if (current_pointer_position.second - 1 >= 0) {
      current_pointer_position.second--;
    }
  } else if (code == "RIGHT") {
    if (current_pointer_position.second + 1 <= columns) {
      eol = texts[current_pointer_position.first].size();
      if (current_pointer_position.second + 1 <= eol) {
        current_pointer_position.second++;
      }
    }
  } else if (code == "DOWN") {
    if (current_pointer_position.first + 1 < lines) {
      current_pointer_position.first++;
      eol = texts[current_pointer_position.first].size();
      if (current_pointer_position.second > eol) {
        current_pointer_position.second = eol;
      }
    }
  }
}

int TextField::locate_eol(int line) { return 0; }

void TextField::set_spacing_line(int spacing) { spacing_line = spacing; }

void TextField::set_spacing_letter(int spacing) { spacing_letter = spacing; }

void TextField::read_input(SDL_Event* event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_BACKSPACE:
        erase();
        break;
      case SDLK_RETURN:
        add_endline();
        break;
      case SDLK_UP:
        move_pointer("UP");
        break;
      case SDLK_DOWN:
        move_pointer("DOWN");
        break;
      case SDLK_LEFT:
        move_pointer("LEFT");
        break;
      case SDLK_RIGHT:
        move_pointer("RIGHT");
        break;
      default:
        break;
    }
  } else if (event->type == SDL_TEXTINPUT) {
    if (!(SDL_GetModState() & KMOD_CTRL &&
          (event->text.text[0] == 'c' || event->text.text[0] == 'C' ||
           event->text.text[0] == 'v' || event->text.text[0] == 'V'))) {
      std::string input = event->text.text;
      write(input[0]);
    }
  }
}

void TextField::update_line() {
  Game& game = Game::get_instance();
  int line = current_pointer_position.first;
  if (texts[line] != "") {
    SDL_Surface* provisory_surface = NULL;
    provisory_surface =
        TTF_RenderText_Blended(font, texts[line].c_str(), font_color);
    SDL_Texture* line_texture =
        SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
    texts_textures[line] = line_texture;
    SDL_Rect renderQuad = {position.first + 10,
                           position.second + (provisory_surface->h * line) + 15,
                           provisory_surface->w, provisory_surface->h};
    texts_rects[line] = renderQuad;
    SDL_FreeSurface(provisory_surface);
  }
}