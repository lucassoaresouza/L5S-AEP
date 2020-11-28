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
    initial_position = object_position;
    set_label_name();
    Engine::Collider& collider = Engine::Collider::get_instance();
    collider.add_object(this);
}

void ProgrammableObject::add_commands(
    command_list new_commands
){
    commands = new_commands;
}

void ProgrammableObject::draw(){
    label_name->draw();
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

void ProgrammableObject::move(int distance, int displacement){
    verify_collisions();
    int real_distance = distance * (move_displacement + displacement);
    if(expected_x == 0 && expected_y == 0 ){
        expected_x = position.first + real_distance;
        expected_y = position.second + real_distance;
    }

    position.first += orientation.first * 3;
    position.second += orientation.second * 3;
    expected_x -= 3;
    expected_y -= 3;

    if(
        position.first >= expected_x ||
        position.second >= expected_y
    ){
        command_index += 1;
        expected_x = 0;
        expected_y = 0;
    }
    label_name->set_position(
        std::make_pair(
            position.first - name_displacement.first,
            position.second - name_displacement.second
        )
    );
    if(!verify_limits()){
        set_initial_state();
    }
}

void ProgrammableObject::run_commands(){
    if(running == false){
        status = "RUNNING_COMMAND_LIST";
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
            move(arg, 0);
        } else if(command_name == "SOUTH"){
            set_direction("SOUTH");
            move(arg, pivot_displacement);
        } else if(command_name == "WEST"){
            set_direction("WEST");
            move(arg, 0);
        } else if(command_name == "EAST"){
            set_direction("EAST");
            move(arg, pivot_displacement);
        }
        if(
            command_index == commands.size() &&
            command_index != 0
        ){
            status = "FINISHED_COMMAND_LIST";
        }
    } else {
        set_initial_state();
    }
}

void ProgrammableObject::set_initial_state(){
    set_position(initial_position);
    set_direction("NORTH");
    commands.clear();
    expected_x = 0;
    expected_y = 0;
    running = false;
    command_index = 0;
    if(label_name){
        label_name->set_position(
            std::make_pair(
                position.first - name_displacement.first,
                position.second - name_displacement.second
            )
        );
    }
    status = "INITIAL_STATE";
}

void ProgrammableObject::set_initial_position(std::pair<int, int> initial){
    initial_position = initial;
}

void ProgrammableObject::set_limits(
    std::pair<int, int> min, std::pair<int,int> max
){
    limits.first = min;
    limits.second = max;
}

bool ProgrammableObject::verify_limits(){
    if(
        position.first < limits.first.first ||
        position.second < limits.first.second ||
        position.first > limits.second.first ||
        position.second > limits.second.second
    ){
        return false;
    }
    return true;
}

void ProgrammableObject::verify_collisions(){
    std::vector<Engine::GameObject*> objects;
    Engine::Collider& collider = Engine::Collider::get_instance();
    objects = collider.verify(this);
    for(auto object : objects){
        if(object->get_name() == "collidable_trail"){
            object->collide();
        }
    }
}

std::string ProgrammableObject::get_status(){
    return status;
}

void ProgrammableObject::set_label_name(){
    UsersManage& user_manage = UsersManage::get_instance();
    std::string name = user_manage.get_current_user()->get_name();
    label_name = new Engine::Field(
        "label-name",
        std::make_pair(
            position.first - name_displacement.first,
            position.second - name_displacement.second
        ),
        std::make_pair(0,0)
    );
    label_name->set_bold(true);
    label_name->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
    label_name->set_text_per_line(name, 0);
    label_name->load();
    
}