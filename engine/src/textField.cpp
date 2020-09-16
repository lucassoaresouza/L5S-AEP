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
    pointer_position.first=0;
    pointer_position.second=0;
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
            text_table[i][j] = "";
            texture_table[i][j] = NULL;
        }
    }
    return true;
}

void TextField::draw(){
    free();
    read_input();
    Game& game = Game::get_instance();
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            SDL_Surface* provisory_surface = NULL;
            std::string aux_value = text_table[i][j];
            if(aux_value == "\n" || aux_value == ""){
                aux_value = " ";
            }
            provisory_surface = TTF_RenderText_Blended(
                font,
                aux_value.c_str(),
                font_color
            );
            texture_table[i][j] = SDL_CreateTextureFromSurface(
                game.get_renderer(),
                provisory_surface
            );
            SDL_Rect renderQuad = {
                provisory_surface->w * j + 10,
                provisory_surface->h * i + 10,
                provisory_surface->w,
                provisory_surface->h
            };
            SDL_FreeSurface(provisory_surface);
            SDL_RenderCopy(
                game.get_renderer(),
                texture_table[i][j],
                NULL,
                &renderQuad
            );
        }
    }
}

void TextField::free(){
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            SDL_DestroyTexture(texture_table[i][j]);
            texture_table[i][j] = NULL;
        }
    }
}

std::string TextField::get_current_text(){
    current_text = "";
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            current_text += text_table[i][j];
        }
    }
    return current_text;
}

void TextField::write(char letter){
    if(pointer_position.first != lines && pointer_position.second != columns){
        text_table[pointer_position.first][pointer_position.second] = letter;
        if(pointer_position.second + 1 < columns){
            pointer_position.second += 1;
        } else {
            if(pointer_position.first + 1 <= lines){
                pointer_position.first += 1;
                pointer_position.second = 0;
            }
        }
    }
}

void TextField::erase(){
    if(pointer_position.first >= 0 && pointer_position.second >= 0){
        if(pointer_position.second - 1 >= 0){
            text_table[pointer_position.first][pointer_position.second - 1] = "";
            pointer_position.second -= 1;
        } else {
            if(pointer_position.first - 1 >= 0){
                pointer_position.first -= 1;
                pointer_position.second = columns;
            }
        }
    }
}

void TextField::add_endline(){
    if(pointer_position.first >= 0 && pointer_position.first < lines){
        text_table[pointer_position.first][pointer_position.second] = "\n";
        pointer_position.first += 1;
        pointer_position.second = 0;
    }
}

void TextField::set_spacing_line(int spacing){
    spacing_line = spacing;
}

void TextField::set_spacing_letter(int spacing){
    spacing_letter = spacing;
}

void TextField::read_input(){
    SDL_Event e;
    SDL_StartTextInput();
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            Game& game = Game::get_instance();
            game.quit = true;
        } else if(e.type == SDL_KEYDOWN){
            if(e.key.keysym.sym == SDLK_BACKSPACE){
                erase();
            } else if(e.key.keysym.sym == SDLK_RETURN){
                add_endline();
            }
        } else if( e.type == SDL_TEXTINPUT ){
            if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) ){
                    std::string input = e.text.text;
                    write(input[0]);
            }
        }
    }
    SDL_StopTextInput();
}