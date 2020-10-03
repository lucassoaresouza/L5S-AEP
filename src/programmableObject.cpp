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
        Engine::Log().print("UP");//angle = 0
        direction_angle = 0;
    } else if(new_direction == "DOWN"){
        Engine::Log().print("DOWN"); //angle = 180
        direction_angle = 180;
    } else if(new_direction == "LEFT"){
        Engine::Log().print("LEFT"); //angle = 270
        direction_angle = 270;
    } else if(new_direction == "RIGHT"){
        Engine::Log().print("RIGHT"); //angle = 90
        direction_angle = 90;
    } else {
        Engine::Log().print("Direcao invalida!");
    }
}

int ProgrammableObject::get_direction(){
    return direction_angle;
}

void ProgrammableObject::read_input(SDL_Event *event){
    if(event->type == SDL_KEYDOWN){
        switch(event->key.keysym.sym){
            case SDLK_a:
                set_direction("LEFT");
                break;
            case SDLK_d:
                set_direction("RIGHT");
                break;
            case SDLK_s:
                set_direction("DOWN");
                break;
            case SDLK_w:
                set_direction("UP");
                break;
            default:
                break;
        }
    }
}