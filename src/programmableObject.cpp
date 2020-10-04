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
    std::vector<Compiler::Command> new_commands
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

void ProgrammableObject::run_commands(){
    if(running == false){
        running = true;
        for(Compiler::Command command : commands){
            std::string command_name = command.name();
            std::vector<uint64_t> args = command.get_args();
            if(command_name == "paraFrente"){
                set_direction("UP");
                move(args[0]);
            } else if(command_name == "paraTras"){
                set_direction("DOWN");
                move(args[0]);
            } else if(command_name == "paraEsquerda"){
                set_direction("LEFT");
                move(args[0]);
            } else if(command_name == "paraDireita"){
                set_direction("RIGHT");
                move(args[0]);
            }
        }
    }
    running = false;
}