#include "../inc/selectRobotMenu.hpp"

using namespace Engine;

SelectRobotMenu::SelectRobotMenu(
    std::string screen_name
){
    set_name(screen_name);
}

void SelectRobotMenu::init(){
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
        add_object(aux_field);

        column_index++;
        if(column_index > 2){
            line_index++;
            column_index=0;
        }
    }

}

void SelectRobotMenu::load(){
    init();
    for(auto object : objects){
        object->load();
    }
}