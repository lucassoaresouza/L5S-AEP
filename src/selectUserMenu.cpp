#include "../inc/selectUserMenu.hpp"

SelectUserMenu::SelectUserMenu(std::string name){
    set_name(name);
}

void SelectUserMenu::init(){
    label_background = new Engine::Field(
        "background",
        label_background_position,
        std::make_pair(350, 175)
    );
    label_background->set_color(0xAAA, 0xAAA, 0xAAA, 0x00);
    add_object(label_background);

    title = new Engine::Field(
        "title",
        title_position,
        std::make_pair(10,10)
    );
    title->set_bold(true);
    title->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
    title->set_text_per_line("Seja bem vindo(a)!",0);
    title->set_color(0xAAA, 0xAAA, 0xAAA, 0x00);
    add_object(title);

    description = new Engine::Field(
        "title",
        description_position,
        std::make_pair(10,10)
    );
    description->set_bold(true);
    description->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
    description->set_text_per_line("Por favor, insira seu nome:",0);
    description->set_color(0xAAA, 0xAAA, 0xAAA, 0x00);
    add_object(description);

    user_input = new Engine::TextField(
        "user_input",
        user_input_position,
        1,
        25
    );
    user_input->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    user_input->set_font_color(0x00, 0x00, 0x00, 0x00);
    add_object(user_input);
}