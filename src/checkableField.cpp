#include "../inc/checkableField.hpp"

CheckableField::CheckableField(std::string object_name,
                               std::pair<int, int> object_position,
                               std::pair<int, int> object_size) {
  set_name(object_name);
  set_position(object_position);
  set_size(object_size);
  for (int i = 0; i < 10; i++) {
    font_texture[i] = NULL;
  }
}

void CheckableField::check() { checked = true; }

void CheckableField::uncheck() { checked = false; }

bool CheckableField::is_checked() { return checked; }

void CheckableField::collide() { check(); }

void CheckableField::set_checked_texture(std::string path) {
  Engine::Game& game = Engine::Game::get_instance();
  checked_texutre_path = path;
  SDL_Surface* provisory_surface = IMG_Load(checked_texutre_path.c_str());
  if (provisory_surface == NULL) {
    std::cout << "Nao foi possivel carregar o sprite" << std::endl;
  } else {
    checked_texture =
        SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
    if (checked_texture == NULL) {
      std::cout << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(provisory_surface);
  }
}

void CheckableField::draw() {
  Engine::Game& game = Engine::Game::get_instance();
  SDL_Rect rect = {
      position.first,
      position.second,
      size.first,
      size.second,
  };

  if (sprite == "") {
    SDL_SetRenderDrawColor(game.get_renderer(), color.r, color.g, color.b,
                           color.a);
    SDL_RenderFillRect(game.get_renderer(), &rect);
  }

  if (texture != NULL) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(game.get_renderer(), texture, NULL, &rect, rotation, NULL,
                     flip);
    if (checked) {
      if (checked_texture != NULL) {
        SDL_RenderCopy(game.get_renderer(), checked_texture, NULL, &rect);
      }
    }
  }
  draw_texts();
}