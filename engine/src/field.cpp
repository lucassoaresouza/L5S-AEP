#include "field.hpp"

using namespace Engine;

Field::Field(
    std::string object_name,
    std::pair<int, int> object_position,
    std::pair<int, int> object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
}

void Field::set_color(Uint64 r, Uint64 g, Uint64 b, Uint64 a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

bool Field::load(){
    free();
    if(sprite != ""){
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
    return true;
};

void Field::draw(){
    Game& game = Game::get_instance();
    SDL_Rect rect = {
        position.first,
        position.second,
        size.first,
        size.second, 
    };
    SDL_SetRenderDrawColor(
        game.get_renderer(),
        color.r,
        color.g,
        color.b,
        color.a 
    );        
    SDL_RenderFillRect(game.get_renderer(), &rect);
    if(texture != NULL){
        SDL_RenderCopy(game.get_renderer(), texture, NULL, &rect);
    }
}
