#include "../inc/dialogBox.hpp"

DialogBox::DialogBox(
    std::string name,
    std::pair<int, int> position,
    std::pair<int, int> size
){
    set_name(name);
    set_position(position);
    set_size(size);
}

bool DialogBox::is_active(){
    return active;
}

void DialogBox::activate(){
    active = true;
}

void DialogBox::deactivate(){
    active = false;
}

void DialogBox::set_icon(
    std::string path,
    std::pair<int, int> obj_position,
    std::pair<int, int> size 
){
    icon = new Engine::Field(
        "dialog-box-icon",
        std::make_pair(
            position.first + obj_position.first,
            position.second + obj_position.second
        ),
        size
    );
    // icon->set_sprite(path);
    icon->set_sprite(path, "");
}

void DialogBox::set_text(
    std::string text,
    std::pair<int, int> obj_position
){
    text_field = new Engine::Field(
        "dialog-box-text",
        std::make_pair(
            position.first + obj_position.first,
            position.second + obj_position.second
        ),
        std::make_pair(0,0)
    );
    text_field->set_bold(true);
    text_field->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
    text_field->set_text_per_line(text, 0);
}

bool DialogBox::load(){
    if(icon){
        icon->load();
    }
    if(text_field){
        text_field->load();
    }
    return true;
}

void DialogBox::draw(){
    Engine::Game& game = Engine::Game::get_instance();
    if(is_active()){
        //draw background
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
        if(icon){
            icon->draw();
        }
        if(text_field){
            text_field->draw();
        }
    }
}