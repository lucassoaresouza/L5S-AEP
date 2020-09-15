#include <iostream>

#include "../inc/game.hpp"

using namespace Engine;

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

bool Game::init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
        Log().print("Houve um problema ao inicializar a SDL");
        success = false;
    }
    window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_dimensions.first,
        instance->window_dimensions.second,
        SDL_WINDOW_SHOWN
    );
    if(!window){
        Log().print("Houve um problema ao inicializar a janela");
        success = false;
    } else {
        renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL){
            Log().print("Nao foi possivel criar o renderer!");
            success = false;
        }
    }
    int imageFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imageFlags) & imageFlags)){
        Log().print("Houve um problema ao inicializar o modulo de imagem da SDL2");
        success = false;
    }
    if(TTF_Init() == -1){
        Log().print("Houve um problema ao inicializar o modulo de textos da SDL2");
        success = false;     
    }
    return success;
}

void Game::close(){
    SDL_DestroyTexture(current_texture);
    current_texture = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    IMG_Quit();
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

        SDL_SetRenderDrawColor(renderer, 0xD3, 0xD3, 0xD3, 0x00);
        SDL_RenderClear(renderer);
        draw_objects();
        SDL_RenderPresent(renderer);
    }
    close();
}

void Game::set_name(std::string game_name){
    name = game_name;
}

std::string Game::get_name(){
    return name;
}

SDL_Renderer *Game::get_renderer(){
    return renderer;
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
        object->load();
    }
}

void Game::draw_objects(){
    for(auto object : objects){
        object->draw();
    }
}