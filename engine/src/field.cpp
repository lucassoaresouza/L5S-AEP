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

void Field::set_font(std::string path, int size){
        font_path = path;
        font_size = size;
        font = TTF_OpenFont(path.c_str(), size);
}

void Field::set_text(std::string new_text){
    text = new_text;
}

void Field::draw(){
    Game& game = Game::get_instance();
    SDL_Rect rect = {
        position.first,
        position.second,
        size.first,
        size.second, 
    };

    if(sprite == ""){
        SDL_SetRenderDrawColor(
            game.get_renderer(),
            color.r,
            color.g,
            color.b,
            color.a 
        );        
        SDL_RenderFillRect(game.get_renderer(), &rect);
    }

    if(texture != NULL){
        SDL_RenderCopy(game.get_renderer(), texture, NULL, &rect);
    }

    if(font != NULL){
        if(is_bold){
            TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        }
        SDL_Surface* font_surface = NULL;
        font_surface = TTF_RenderText_Blended(
            font,
            text.c_str(),
            color
        );
        SDL_Texture *font_texture = SDL_CreateTextureFromSurface(
            game.get_renderer(),
            font_surface
        );
        SDL_Rect renderQuad = {
            position.first + (size.first / 2) - (font_surface->w / 2),
            position.second + (size.second / 2) - (font_surface->h / 2),
            font_surface->w,
            font_surface->h
        };
        SDL_FreeSurface(font_surface);
        SDL_RenderCopy(
            game.get_renderer(),
            font_texture,
            NULL,
            &renderQuad
        );
    }
}

void Field::set_bold(bool bold){
    is_bold = bold;
}