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
}
