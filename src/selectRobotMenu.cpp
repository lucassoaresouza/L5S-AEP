#include "../inc/selectRobotMenu.hpp"

using namespace Engine;

SelectRobotMenu::SelectRobotMenu(
    std::string screen_name
){
    set_name(screen_name);
}

void SelectRobotMenu::init(){
    init_background();
    init_robots();
    init_challenge_creator();
    init_init_button();
    init_user();
}

void SelectRobotMenu::init_background(){
    background_field = new Field(
        "selector_field",
        background_position,
        std::make_pair(390,258)
    );
    add_object(background_field);

    selector_field = new Selector(
        "selector_field",
        selector_field_position,
        std::make_pair(70,70),
        2,
        3,
        128
    );
    selector_field->set_sprite(
        "./assets/sprites/tiles/border.png"
    );
    add_object(selector_field);
}

void SelectRobotMenu::init_robots(){
    Engine::Collider& collider = Engine::Collider::get_instance();
    std::string robot_base_path = "./assets/sprites/bots/bot_";
    std::pair<int, int> aux_robot_position;
    int line_index = 0;
    int column_index = 0;
    for(int i = 97; i < 103; i++){
        char aux_letter = i;
        aux_robot_position.first = (
            robots_position.first + (column_index * 128) + 32
        );
        aux_robot_position.second = (
            robots_position.second + (line_index * 128) + 32
        );

        Field* aux_field = new Field(
            "robot_" + i,
            aux_robot_position,
            std::make_pair(64,64)
        );
        aux_field->set_sprite(
            robot_base_path+aux_letter+".png",
            ""
        );
        robots.push_back(aux_field);
        collider.add_object(aux_field);
        add_object(aux_field);

        column_index++;
        if(column_index > 2){
            line_index++;
            column_index=0;
        }
    }
}

void SelectRobotMenu::init_challenge_creator(){
    challenge_creator = new ChallengeCreator();
    challenge_creator->create_maps("./data/levels");
}

void SelectRobotMenu::init_init_button(){
    std::pair<int, int> button_size(128,100);
    InitButton* init_challenge_button = new InitButton(
        "init_challenge_button",
        button_position,
        button_size
    );
    init_challenge_button->set_sprites(
        "./assets/sprites/buttons/button1.png",
        "./assets/sprites/buttons/button2.png"
    );
    init_challenge_button->set_selector(selector_field);
    init_challenge_button->set_challenge_creator(challenge_creator);
    init_challenge_button->activate();
    add_object(init_challenge_button);
}

void SelectRobotMenu::init_user(){
    UsersManage& users_manage = UsersManage::get_instance();
    current_user = users_manage.get_current_user();
}
