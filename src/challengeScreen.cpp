#include "../inc/challengeScreen.hpp"

using namespace Engine;

ChallengeScreen::ChallengeScreen(
    std::string screen_name,
    Challenge* new_challenge
){
    set_name(screen_name);
    challenge = new_challenge;
}

void ChallengeScreen::init(){
    remove_all_objects();

    //Map initialization
    map = challenge->get_actual_map();
    map->set_position(map_position);
    map->init();
    std::pair<std::pair<int, int>,std::pair<int, int>> limits = map->get_limits();

    //Player initialization
    std::string player_object_name="aviao";
    std::pair<int, int> player_object_position;
    player_object_position = map->get_obj_initial_position();
    std::pair<int, int> player_object_size(32, 32);
    player_object = new ProgrammableObject(
        player_object_name,
        player_object_position,
        player_object_size
    );
    player_object->set_sprite("./assets/bots/B-25c.png");
    player_object->set_limits(limits.first, limits.second);

    //Textfield initialization
    std::string text_field_name="textfield";
    std::pair<int, int> text_field_position(10, 10);
    TextField* text_field = new TextField(text_field_name, text_field_position, 35, 40);
    text_field->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    text_field->set_font_color(0x00, 0x00, 0x00, 0x00);

    //Compiler initialization
    AEPCompiler* compiler = new AEPCompiler();

    //Button initialization
    std::string button_name = "button";
    std::pair<int, int> button_position(120,660);
    std::pair<int, int> button_size(128,64);
    CompilerButton* button = new CompilerButton(button_name, button_position, button_size);
    button->set_sprites(
        "./assets/buttons/button1.png",
        "./assets/buttons/button2.png"
    );
    button->set_compiler(compiler);
    button->set_programmable(player_object);
    button->set_text_field(text_field);

    // Add objects
    add_object(map);
    add_object(player_object);
    add_object(text_field);
    add_object(button);
}

void ChallengeScreen::load(){
    init();
    for(auto object : objects){
        object->load();
    }
}

void ChallengeScreen::draw(){
    verify_programmable_object_status();
    for(auto object : objects){
        object->draw();
    }
}

void ChallengeScreen::verify_programmable_object_status(){
    if(player_object->get_status() == "FINISHED_COMMAND_LIST"){
        if(map->verify_all_trail_checked()){
            map->set_completed(true);
            load();
            std::cout << "ganhei!" << std::endl;
        } else {
            map->reset_all_trail_checks();
        }
    }
}
