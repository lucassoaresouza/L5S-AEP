#include "../inc/programmableObject.hpp"


ProgrammableObject::ProgrammableObject(
    std::string object_name,
    std::pair<int, int> object_position,
    std::pair<int, int> object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
    set_direction("NORTH");
}

void ProgrammableObject::add_commands(
    command_list new_commands
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
    execute();
}

void ProgrammableObject::set_direction(std::string new_direction){
    if(new_direction == "NORTH"){
        direction_angle = 0;
        orientation.first = 0;
        orientation.second = -1;

    } else if(new_direction == "SOUTH"){
        direction_angle = 180;
        orientation.first = 0;
        orientation.second = 1;

    } else if(new_direction == "WEST"){
        direction_angle = 270;
        orientation.first = -1;
        orientation.second = 0;

    } else if(new_direction == "EAST"){
        direction_angle = 90;
        orientation.first = 1;
        orientation.second = 0;
    } else {
        Engine::Log().print("Direcao invalida!");
    }
}

void ProgrammableObject::move(int distance){
    if(expected_x == 0 && expected_y == 0 ){
        expected_x = position.first + distance;
        expected_y = position.second + distance;
    }

    position.first += orientation.first * 1;
    position.second += orientation.second * 1;
    expected_x -= 1;
    expected_y -= 1;

    if(
        position.first >= expected_x ||
        position.second >= expected_y
    ){
        command_index += 1;
        expected_x = 0;
        expected_y = 0;
    }
}

void ProgrammableObject::run_commands(){
    if(running == false){
        running = true;
    } else {
        Engine::Log().print("Executando a lista de comandos anterior!");
    }
}

void ProgrammableObject::execute(){
    if(command_index < commands.size() && running == true){
        std::string command_name = commands[command_index].first;
        double arg = commands[command_index].second;
        if(command_name == "NORTH"){
            set_direction("NORTH");
            move(arg);
        } else if(command_name == "SOUTH"){
            set_direction("SOUTH");
            move(arg);
        } else if(command_name == "WEST"){
            set_direction("WEST");
            move(arg);
        } else if(command_name == "EAST"){
            set_direction("EAST");
            move(arg);
        }
    } else {
        set_initial_state();
    }
}

void ProgrammableObject::set_initial_state(){
    std::pair<int, int>position(405+(7*32),450);
    set_position(position);
    set_direction("NORTH");
    commands.clear();
    expected_x = 0;
    expected_y = 0;
    running = false;
    command_index = 0;
}
