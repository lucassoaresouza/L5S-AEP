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
    //Map initialization
    if(!challenge->completed()){
        map = challenge->get_actual_map();
    } else {
        Engine::Game& game = Engine::Game::get_instance();
        game.load_screen("select_robot");
    }
    map->set_position(map_position);
    map->init();
    std::pair<std::pair<int, int>,std::pair<int, int>> limits = (
        map->get_limits()
    );

    //Player initialization
    std::pair<int, int> player_object_position;
    player_object_position = map->get_obj_initial_position();
    std::pair<int, int> player_object_size(32, 32);
    player_object = new ProgrammableObject(
        "player_object",
        player_object_position,
        player_object_size
    );
    player_object->set_sprite(player_sprite);
    player_object->set_limits(limits.first, limits.second);

    //Textfield initialization
    TextField* text_field = new TextField(
        "textfield",
        text_field_position,
        35,
        40
    );
    text_field->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    text_field->set_font_color(0x00, 0x00, 0x00, 0x00);

    //Compiler initialization
    AEPCompiler* compiler = new AEPCompiler();

    //Button initialization
    std::pair<int, int> button_size(128,64);
    CompilerButton* button = new CompilerButton(
        "button",
        compiler_button_position,
        button_size
    );
    button->set_sprites(
        "./assets/sprites/buttons/button1.png",
        "./assets/sprites/buttons/button2.png"
    );
    button->set_compiler(compiler);
    button->set_programmable(player_object);
    button->set_text_field(text_field);

    //Console initialization
    console = new Engine::Field(
        "console",
        console_position,
        std::make_pair(572,117)
    );
    console->set_bold(true);
    console->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
    console->set_text_per_line("Desafio:",0);
    console->set_text_per_line("Dica:",1);
    console->set_text_per_line("Status:",2);
    console->set_text_per_line("Campos Cobertos:",3);

    // Add objects
    add_object(map);
    add_object(player_object);
    add_object(text_field);
    add_object(button);
    add_object(console);
}

void ChallengeScreen::draw(){
    verify_programmable_object_status();
    for(auto object : objects){
        object->draw();
    }
}

void ChallengeScreen::verify_programmable_object_status(){
    if(player_object->get_status() == "INITIAL_STATE"){
        map->reset_all_trail_checks();
        console->set_text_per_line("Desafio: " + map->get_name(),0);
        console->set_text_per_line("Dica: " + map->get_text_info(),1);
        std::string console_status = "Inicializado";
        console->set_text_per_line("Status: " + console_status,2);
        console->set_text_per_line(
            "Campos Cobertos: 0/" + std::to_string(
                map->get_all_checked_field_count()
            ),
            3
        );
    } else if(player_object->get_status() == "RUNNING_COMMAND_LIST"){
        std::string console_status = "Executando comandos!";
        console->set_text_per_line("Status: " + console_status,2);
        char bar = '/';
        console->set_text_per_line(
            "Campos Cobertos: " +
            std::to_string(map->get_checked_field_count()) + 
            bar +
            std::to_string(map->get_all_checked_field_count()),
            3
        );
    } else if(player_object->get_status() == "FINISHED_COMMAND_LIST"){
        if(map->verify_all_trail_checked()){
            map->set_completed(true);
            remove_all_objects();
            Engine::Collider& collider = Engine::Collider::get_instance();
            collider.remove_all_objects();
            load();
            
            std::cout << "ganhei!" << std::endl;
        } else {
            map->reset_all_trail_checks();
        }
    }
}

void ChallengeScreen::set_player_sprite(std::string path){
    player_sprite = path;
}