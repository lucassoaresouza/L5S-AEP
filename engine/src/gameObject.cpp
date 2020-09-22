#include "../inc/gameObject.hpp"
#include "../inc/game.hpp"

using namespace Engine;

GameObject::GameObject(){};

GameObject::GameObject(
    std::string object_name,
    std::pair<int, int> object_position,
    std::pair<int, int> object_size
){
    name = object_name;
    position = object_position;
    size = object_size;
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
std::string GameObject::get_sprite(){
    return sprite;
}


void GameObject::set_sprite(std::string path){
    sprite = path;
}
bool GameObject::load(){
    free();
    Game& game = Game::get_instance();
    SDL_Texture* in_load_texture = NULL;
    SDL_Surface* provisory_surface = IMG_Load(sprite.c_str());
    if(provisory_surface == NULL){
        Log().print("Nao foi possivel carregar o sprite!");
    } else {
        in_load_texture = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
        if(in_load_texture == NULL){
            Log().print(SDL_GetError());
        }
        SDL_FreeSurface(provisory_surface);
    }
    texture = in_load_texture;
    return texture != NULL;
}

void GameObject::draw(){
    Game& game = Game::get_instance();
    SDL_Rect ret = {
        position.first,
        position.second,
        size.first,
        size.second
    };
    SDL_RenderCopy(game.get_renderer(), texture, NULL, &ret);
}
void GameObject::free(){
    if(texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

std::string GameObject::get_name(){
    return name;
}

void GameObject::read_input(SDL_Event *event){}

void GameObject::set_texture(SDL_Texture* new_texture){
    texture = new_texture;
}