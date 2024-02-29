#include "../inc/game.hpp"

#include <iostream>

using namespace Engine;

Game* Game::instance = NULL;

Game& Game::get_instance() {
  if (!instance) {
    Log().print("Primeiramente inicialize uma instancia");
    std::string default_name = "screen";
    std::pair<int, int> default_screen(800, 600);
    return Game::initialize(default_name, default_screen);
  } else {
    return *instance;
  }
}

Game& Game::initialize(std::string game_name,
                       std::pair<int, int> window_dimensions) {
  if (!instance) {
    instance = new Game();
    instance->set_information(game_name, window_dimensions);
    instance->init();
    instance->screen_manage = new ScreenManage();
    instance->timer = new Timer();
    instance->cap_fps_timer = new Timer();
  }
  return *instance;
}

void Game::set_information(std::string game_name,
                           std::pair<int, int> window_dimensions) {
  set_name(game_name);
  set_window_dimensions(window_dimensions);
}

bool Game::init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    Log().print("Houve um problema ao inicializar a SDL");
    success = false;
  }
  window =
      SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, window_dimensions.first,
                       instance->window_dimensions.second, SDL_WINDOW_SHOWN);
  if (!window) {
    Log().print("Houve um problema ao inicializar a janela");
    success = false;
  } else {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
      Log().print("Nao foi possivel criar o renderer!");
      success = false;
    }
  }
  int imageFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imageFlags) & imageFlags)) {
    Log().print("Houve um problema ao inicializar o modulo de imagem da SDL2");
    success = false;
  }
  if (TTF_Init() == -1) {
    Log().print("Houve um problema ao inicializar o modulo de textos da SDL2");
    success = false;
  }
  return success;
}

void Game::close() {
  SDL_DestroyTexture(game_background);
  game_background = NULL;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  window = NULL;
  renderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

void Game::run() {
  timer->start();
  while (!quit) {
    cap_fps_timer->start();
    read_input();
    SDL_RenderClear(renderer);
    draw_background();
    draw_screen();
    SDL_RenderPresent(renderer);
    frames_count++;
    calculate_fps();
    cap_max_fps();
  }
  close();
}

void Game::set_name(std::string game_name) { name = game_name; }

std::string Game::get_name() { return name; }

SDL_Renderer* Game::get_renderer() { return renderer; }

void Game::set_window_dimensions(std::pair<int, int> dimensions) {
  window_dimensions = dimensions;
}

std::pair<int, int> Game::get_window_dimensions() { return window_dimensions; }

void Game::load_screen(std::string screen_name) {
  if (actual_screen) {
    actual_screen->free();
    actual_screen = NULL;
  }
  actual_screen = screen_manage->get_screen(screen_name);
  if (actual_screen) {
    actual_screen->load();
  } else {
    Log().print("Screen not found!");
  }
}

void Game::draw_screen() {
  if (actual_screen) {
    actual_screen->draw();
  } else {
    Log().print("Screen not found!");
  }
}

void Game::read_input() {
  input_receiver.run();
  if (input_receiver.get_last_input()->type == SDL_QUIT) {
    quit = true;
  }
}

void Game::add_screen(Screen* screen) { screen_manage->add_screen(screen); }

void Game::calculate_fps() {
  fps = frames_count / (timer->get_ticks() / 1000.f);
  // std::cout << "FPS: " << fps << std::endl;
}

void Game::cap_max_fps() {
  int frame_ticks = cap_fps_timer->get_ticks();
  if (frame_ticks < cap_fps) {
    SDL_Delay(cap_fps - frame_ticks);
  }
}

void Game::set_game_background(std::string path) {
  if (renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL) {
      Log().print("Nao foi possivel carregar o sprite!");
    } else {
      game_background = SDL_CreateTextureFromSurface(renderer, surface);
      if (game_background == NULL) {
        Log().print(SDL_GetError());
      }
      SDL_FreeSurface(surface);
    }
  }
}

void Game::draw_background() {
  if (game_background) {
    SDL_Rect ret = {0, 0, window_dimensions.first, window_dimensions.second};
    SDL_RenderCopy(renderer, game_background, NULL, &ret);
  }
}

bool Game::search_screen(std::string screen_name) {
  return screen_manage->search_screen(screen_name);
}