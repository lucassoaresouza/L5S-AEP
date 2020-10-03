#include "../inc/programmableObject.hpp"


ProgrammableObject::ProgrammableObject(
    std::string object_name,
    std::pair<int, int> object_position,
    std::pair<int, int> object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
    set_direction("UP");
}

void ProgrammableObject::add_commands(
    std::vector<Compiler::Command>& new_commands
){
    commands = new_commands;
}

void ProgrammableObject::draw(){
    Engine::Game& game = Engine::Game::get_instance();
    SDL_Rect ret = {
        position.first,
        position.second,
        size.first,
        size.second
    };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(
        game.get_renderer(),
        texture,
        NULL,
        &ret,
        direction_angle,
        NULL,
        flip
    );
}

void ProgrammableObject::set_direction(std::string new_direction){
    if(new_direction == "UP"){
        direction_angle = 0;
        orientation.first = 0;
        orientation.second = -1;

    } else if(new_direction == "DOWN"){
        direction_angle = 180;
        orientation.first = 0;
        orientation.second = 1;

    } else if(new_direction == "LEFT"){
        direction_angle = 270;
        orientation.first = -1;
        orientation.second = 0;

    } else if(new_direction == "RIGHT"){
        direction_angle = 90;
        orientation.first = 1;
        orientation.second = 0;
    } else {
        Engine::Log().print("Direcao invalida!");
    }
}

void ProgrammableObject::move(int distance){
    position.first += orientation.first * distance;
    position.second += orientation.second * distance;
}

void ProgrammableObject::read_input(SDL_Event *event){
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_a:
                set_direction("LEFT");
                move(10);
                break;
            case SDLK_d:
                set_direction("RIGHT");
                move(10);
                break;
            case SDLK_s:
                set_direction("DOWN");
                move(10);
                break;
            case SDLK_w:
                set_direction("UP");
                move(10);
                break;
            default:
                break;
        }
    }
}