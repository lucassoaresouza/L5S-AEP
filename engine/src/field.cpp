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
    for(int i = 0; i < 10; i++){
        text[i] = "";
        font_texture[i] = NULL;
        text_quads[i] = {0, 0, 0, 0};
    }
}

void Field::set_color(Uint64 r, Uint64 g, Uint64 b, Uint64 a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

bool Field::load(){
    if(sprite != ""){
        Game& game = Game::get_instance();
        SDL_Texture* in_load_texture = NULL;
        SDL_Surface* provisory_surface = IMG_Load(sprite.c_str());
        if(provisory_surface == NULL){
            Log().print("Nao foi possivel carregar o sprite!");
        } else {
            in_load_texture = SDL_CreateTextureFromSurface(
                game.get_renderer(),
                provisory_surface
            );
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
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_RenderCopyEx(
            game.get_renderer(),
            texture,
            NULL,
            &rect,
            rotation,
            NULL,
            flip
        );
    }

    draw_texts();
}

void Field::draw_texts(){
    Game& game = Game::get_instance();
    for(int i = 0; i < 10; i++){
        if(font_texture[i]){
            SDL_RenderCopy(
                game.get_renderer(),
                font_texture[i],
                NULL,
                &text_quads[i]
            );
        }
    }
}

void Field::set_bold(bool bold){
    is_bold = bold;
}

void Field::free(){
    SDL_DestroyTexture(texture);
    for(int i = 0; i < 10; i++){
        if(font_texture[i] != NULL){
            SDL_DestroyTexture(font_texture[i]);
        }
    }
}

void Field::set_text_per_line(std::string new_text, int line){
    Game& game = Game::get_instance();
    text[line] = new_text;
    SDL_Color black_font_color = {0x0, 0x0, 0x0, 0x0};
    if(text[line] != ""){
        if(is_bold){
            TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        }
        SDL_Surface* font_surface = NULL;
        font_surface = TTF_RenderText_Blended(
            font,
            text[line].c_str(),
            black_font_color
        );
        text_quads[line] = {
            position.first+15,
            position.second+15+(font_surface->h * line),
            font_surface->w,
            font_surface->h
        };
        SDL_Texture* aux_texture = SDL_CreateTextureFromSurface(
            game.get_renderer(),
            font_surface
        );
        font_texture[line] = aux_texture;
        SDL_FreeSurface(font_surface);
    }
}

void Field::set_sprite(std::string path, std::string orientation){
    sprite = path;
    if(orientation == "UP-LEFT"){
        rotation = 0;
    } else if(orientation == "DOWN-LEFT"){
        rotation = 90;
    } else if(orientation == "DOWN-RIGHT"){
        rotation = 180;
    } else if(orientation == "UP-RIGHT"){
        rotation = 270;
    } else {
        rotation = 0;
    }
}