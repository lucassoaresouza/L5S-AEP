#include "../inc/initUserButton.hpp"

InitUserButton::InitUserButton(
    std::string object_name,
    std::pair<int,int>object_position,
    std::pair<int,int>object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
}

void InitUserButton::set_user_input(Engine::TextField* input){
    user_input = input;
}

void InitUserButton::execute(){
    if(is_active){
        std::string user_name = user_input->get_current_text();
        if(user_name != ""){
            UsersManage& user_manage = UsersManage::get_instance();
            User* user = user_manage.get_user(user_name);
            if(!user){
                user = new User(user_name);
                user_manage.add_user(user);
            }
            user_manage.set_current_user(user);
            Engine::Game& game = Engine::Game::get_instance();
            game.load_screen("select_robot");
            deactivate();
        } else {
            std::cout << "Nome nao pode ser vazio!" << std::endl;
        }
    }
}