#include <iostream>
#include "../inc/gameObject.hpp"
#include "../inc/game.hpp"

using namespace Engine;

GameObject::GameObject(){};

GameObject::GameObject(
    std::string object_name,
    std::pair<int, int> object_position
){
    name = object_name;
    position = object_position;
}

void GameObject::set_position(std::pair <int, int> object_position){
    position = object_position;
};
void GameObject::set_name(std::string object_name){
    name = object_name;
};
void GameObject::set_size(std::pair<int, int> object_size){
    size = object_size;
};

std::pair<int, int> GameObject::get_position(){
    return position;
};
int GameObject::get_position_x(){
    return position.first;
};
int GameObject::get_position_y(){
    return position.second;
};

std::pair<int, int> GameObject::get_size(){
    return size;
};
int GameObject::get_width(){
    return size.first;
};
int GameObject::get_height(){
    return size.second;
};


void GameObject::set_sprite(std::string path){
    sprite = path;
}
SDL_Texture* GameObject::load(){
    Game& game = Game::get_instance();

    SDL_Surface * loadedSurface = IMG_Load(sprite.c_str());
    if(loadedSurface == NULL){
        Log().print("Nao foi possivel carregar o sprite!");
    } else {
        texture = SDL_CreateTextureFromSurface(game.get_renderer(), loadedSurface);
        if(texture == NULL){
            Log().print(SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    Log().print("Objeto carregado!");
    return texture;
}
