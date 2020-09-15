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
    allocate_tables();
}

void TextField::allocate_tables(){
    text_table = new std::string *[lines];
    texture_table = new SDL_Texture **[lines];
    for(int i = 0; i < lines; i++){
        text_table[i] = new std::string[columns];
        texture_table[i] = new SDL_Texture *[columns];
    }
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
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            text_table[i][j] = "A";
            SDL_Surface* provisory_surface = TTF_RenderText_Shaded(font, text_table[i][j].c_str(), font_color, font_background_color);
            texture_table[i][j] = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
            SDL_FreeSurface(provisory_surface);
        }
    }
    return true;
}

void TextField::draw(){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            texture_table[i][j] = NULL;
        }
    }

    Game& game = Game::get_instance();
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            SDL_Surface* provisory_surface = NULL;
            if(text_table[i][j] != ""){
                provisory_surface = TTF_RenderText_Shaded( font, text_table[i][j].c_str(), font_color, font_background_color);
                texture_table[i][j] = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface); 
            } else {
                std::string empty_string = " ";
                provisory_surface = TTF_RenderText_Shaded( font, empty_string.c_str(), font_color, font_background_color);
                texture_table[i][j] = SDL_CreateTextureFromSurface(game.get_renderer(), provisory_surface);
            }
            SDL_Rect renderQuad = {provisory_surface->w*j+10, provisory_surface->h*i+10, provisory_surface->w, provisory_surface->h};
            SDL_FreeSurface(provisory_surface);
            SDL_RenderCopy(game.get_renderer(), texture_table[i][j], NULL, &renderQuad);
        }
    }
}