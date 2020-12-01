#include "../inc/toScreenButton.hpp"

ToScreenButton::ToScreenButton(
    std::string object_name,
    std::pair<int,int>object_position,
    std::pair<int,int>object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
}

void ToScreenButton::set_screen_name(std::string name){
    screen_name = name;
}

void ToScreenButton::execute(){
    if(is_active && screen_name != ""){
        Engine::Game& game = Engine::Game::get_instance();
        game.load_screen(screen_name);
        deactivate();
    }
}