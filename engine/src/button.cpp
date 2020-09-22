#include "../inc/button.hpp"

using namespace Engine;

Button::Button(
    std::string object_name,
    std::pair<int,int>object_position,
        std::pair<int,int>object_size
){
    set_name(object_name);
    set_size(object_size);
    set_position(object_position);
}

void Button::set_sprites(
    std::string sprite_not_pressed,
    std::string sprite_pressed
){
    set_sprite(sprite_not_pressed);
    pressed_sprite = sprite_pressed;
}

void Button::activate(){
    is_active = true;
}

void Button::deactivate(){
    is_active = false;
}

bool Button::was_pressed(int x, int y){
    std::pair<int, int> current_possition;
    std::pair<int, int> current_size;
    current_possition = get_position();
    current_size = get_size();
    if(
        x >= current_possition.first &&
        x <= current_possition.first + current_size.first &&
        y >= current_possition.second &&
        y <= current_possition.second + current_size.second
    ){
        return true;
    } else {
        return false;
    }
}

void Button::read_input(SDL_Event *event){
    if(event->type == SDL_MOUSEBUTTONDOWN){
        int x;
        int y;
        SDL_GetMouseState( &x, &y);
        if(was_pressed(x,y)){
            pressed = true;
            set_texture(pressed_texture);
            execute();
        }
    } else if(event->type == SDL_MOUSEBUTTONUP){
        if(pressed){
            pressed = false;
            set_texture(not_pressed_texture);
        }
    }
}

bool Button::load(){
    free();

    Game& game = Game::get_instance();
    SDL_Texture* in_load_not_pressed_texture = NULL;
    SDL_Texture* in_load_pressed_texture = NULL;
    std::string not_pressed_sprite = get_sprite();
    SDL_Surface* provisory_not_pressed_surface = IMG_Load(
        not_pressed_sprite.c_str()
    );
    SDL_Surface* provisory_pressed_surface = IMG_Load(
        pressed_sprite.c_str()
    );

    if(
        provisory_not_pressed_surface == NULL ||
        provisory_pressed_surface == NULL
    ){
        Log().print("Nao foi possivel carregar os sprites!");
    } else {
        in_load_not_pressed_texture = SDL_CreateTextureFromSurface(
            game.get_renderer(),
            provisory_not_pressed_surface
        );
        in_load_pressed_texture = SDL_CreateTextureFromSurface(
            game.get_renderer(),
            provisory_pressed_surface
        );
        if(
            in_load_not_pressed_texture == NULL ||
            in_load_pressed_texture == NULL
        ){
            Log().print(SDL_GetError());
        }
        SDL_FreeSurface(provisory_not_pressed_surface);
        SDL_FreeSurface(provisory_pressed_surface);
    }
    not_pressed_texture = in_load_not_pressed_texture;
    pressed_texture = in_load_pressed_texture;
    set_texture(not_pressed_texture);
    return not_pressed_texture != NULL && pressed_texture != NULL;
}
