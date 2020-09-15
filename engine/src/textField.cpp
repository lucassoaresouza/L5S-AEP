#include <string>

#include "../inc/textField.hpp"
#include "game.hpp"

using namespace Engine;

TextField::TextField(
    std::string object_name,
    std::pair<int, int> object_position,
    int max_lines,
    int max_columns
){
    name = object_name;
    position = object_position;
    lines = max_lines;
    columns = max_columns;
}

void TextField::set_font(std::string path, int size){
    font_path = path;
    font_size = size;
}

void TextField::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 alfa){
    font_color = {r, g, b, alfa};
}

bool TextField::load(){
    Game& game = Game::get_instance();
    font = TTF_OpenFont(font_path.c_str(), font_size);
    if(font == NULL){
        Log().print("Houve um problema ao carregar a fonte!");
    }
    SDL_Surface* provisory_surface = TTF_RenderText_Solid(font, current_text.c_str(), font_color);
    texture = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
    return texture != NULL;
}

void TextField::draw(){
    Game& game = Game::get_instance();
    if(current_text != ""){
        SDL_Surface* provisory_surface = TTF_RenderText_Solid( font, current_text.c_str(), font_color);
        texture = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface); 
    } else {
        std::string empty_string = " ";
        SDL_Surface* provisory_surface = TTF_RenderText_Solid( font, empty_string.c_str(), font_color );
        texture = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
    }
    SDL_Rect renderQuad = {0,0 , 10*28, 30};
    SDL_RenderCopy(game.get_renderer(), texture, NULL, &renderQuad);
}