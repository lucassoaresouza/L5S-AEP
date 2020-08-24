#include "game.hpp"
#include <iostream>


Game* Game::instance = NULL;

Game& Game::get_instance(){
    if(!instance){
        Log().print("Primeiramente inicialize uma instancia");
    } else {
        return *instance;
    }
}

Game& Game::initialize(
    std::string game_name,
    std::pair<int, int> window_dimensions
){  
    if(!instance){
        instance = new Game();
        instance->set_information(game_name, window_dimensions);
        instance->init();
    }
    return *instance;
}

void Game::set_information(
    std::string game_name,
    std::pair<int, int> window_dimensions
){
    set_name(game_name);
    set_window_dimensions(window_dimensions);
}

void Game::init(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
        Log().print("Houve um problema ao inicializar a SDL");
    }
    window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_dimensions.first,
        instance->window_dimensions.second,
        SDL_WINDOW_SHOWN
    );
    if(!window){
        Log().print("Houve um problema ao inicializar a janela");
    } else {
        default_surface = SDL_GetWindowSurface(window);
        SDL_FillRect(
            default_surface,
            NULL,
            SDL_MapRGB(
                default_surface->format,
                0xFF, 0xFF, 0xFF
            )
        );
    }
}

void Game::close(){
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run(){
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
        }
        SDL_UpdateWindowSurface(window);
    }
    close();
}

void Game::set_name(std::string game_name){
    name = game_name;
}

std::string Game::get_name(){
    return name;
}

void Game::set_window_dimensions(std::pair<int, int> dimensions){
  window_dimensions = dimensions;
}

std::pair<int, int> Game::get_window_dimensions(){
  return window_dimensions;
}

void Game::add_object(GameObject* object){
    objects.push_back(object);
    std::cout << "Objeto adicionado!" << std::endl;
}

void Game::load_objects(){
    for(auto object : objects){
        std::cout << "Objeto carregado!" << std::endl;
    }
}

void Game::draw_objects(){
    for(auto object : objects){
        std::cout << "Desenhando objeto!" << std::endl;
    }
}