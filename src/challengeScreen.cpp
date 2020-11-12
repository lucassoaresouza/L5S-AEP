#include "../inc/challengeScreen.hpp"

using namespace Engine;

ChallengeScreen::ChallengeScreen(std::string screen_name){
    set_name(screen_name);
}

void ChallengeScreen::init(){
    //Map initialization
    std::string map_name="challenge";
    std::pair<int, int> map_posititon(405, 10);
    std::string map_path = "./levels/level_one/challenge_a.aep";
    ChallengeMap* map = new ChallengeMap(map_name, map_posititon, map_path);
    std::pair<std::pair<int, int>,std::pair<int, int>> limits = map->get_limits();

    // //Console initialization
    // std::string console_name="console";
    // std::pair<int, int> console_posititon(405, ((15*32)+15));
    // std::pair<int, int> console_size(19*32, 181);
    // Field* console = new Field(console_name, console_posititon, console_size);
    // console->set_color(0x99, 0x99, 0x99, 0x99);

    //Player initialization
    std::string player_object_name="aviao";
    std::pair<int, int> player_object_position;
    player_object_position = map->get_possible_position(11,3);
    std::pair<int, int> player_object_size(32, 32);
    ProgrammableObject* player_object = new ProgrammableObject(
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

    //Add objects
    add_object(map);
    add_object(player_object);
    add_object(text_field);
    // add_object(console);
    add_object(button);
}

void ChallengeScreen::load(){
    init();
    for(auto object : objects){
        object->load();
    }
}