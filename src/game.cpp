#include "game.hpp"
#include <iostream>


Game* Game::instance = NULL;

Game& Game::get_instance(){
    if(!instance){
        std::cout << "Primeiramente inicialize uma instancia" << std::endl;
    } else {
        return *instance;
    }
}

Game& Game::initialize(std::string game_name, std::pair<int, int> window_dimensions){
    
    if(!instance){
        instance = new Game();
        instance->set_information(game_name, window_dimensions);
        instance->init();
    }

    return *instance;
}

void Game::set_information(std::string game_name, std::pair<int, int> window_dimensions){
    set_name(game_name);
    set_window_dimensions(window_dimensions);
}

void Game::init(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
        std::cout << "Houve um problema ao inicializar a SDL" << std::endl;
    }
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_dimensions.first, window_dimensions.second, SDL_WINDOW_SHOWN);
    if(!window){
        std::cout << "Houve um problema ao inicializar a janela" << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        std::cout << "Houve um problema ao inicializar o renderer" << std::endl;
    }
}

void Game::close(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}

void Game::run(){
    SDL_Event e;
    
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
                std::cout << "AAAAAAAAAAAAAAAHHHH" << std::endl;
            }
        }
    }

    close();
}

void Game::set_name(std::string game_name){
    name = game_name;
}

std::string Game::get_name(){
    return name;
}

void Game::set_window_dimensions(std::pair<int, int> window_dimensions){
  window_dimensions = window_dimensions;
}

std::pair<int, int> Game::get_window_dimensions(){
  return window_dimensions;
}
