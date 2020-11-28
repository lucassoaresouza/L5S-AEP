#include "../inc/selectUserMenu.hpp"

SelectUserMenu::SelectUserMenu(std::string name){
    set_name(name);
}

void SelectUserMenu::init(){
    std::cout << "load load load" << std::endl;
    init_background();
    init_texts();
    init_user_input();
    // init_init_button();
}

void SelectUserMenu::init_background(){
    label_background = new Engine::Field(
        "background",
        label_background_position,
        std::make_pair(350, 175)
    );
    label_background->set_color(0xAAA, 0xAAA, 0xAAA, 0x00);
    add_object(label_background);
}

void SelectUserMenu::init_texts(){
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
}

void SelectUserMenu::init_user_input(){
    user_input = new Engine::TextField(
        "user_input",
        user_input_position,
        1,
        25
    );
    user_input->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    user_input->set_font_color(0x00, 0x00, 0x00, 0x00);
    add_object_with_input(user_input);
}

void SelectUserMenu::init_init_button(){
    init_button = new InitUserButton(
        "init_user_button",
        init_button_position,
        std::make_pair(100,35)
    );
    init_button->set_sprites(
        "./assets/sprites/buttons/button1.png",
        "./assets/sprites/buttons/button2.png"
    );
    init_button->set_user_input(user_input);
    init_button->activate();
    add_object_with_input(init_button);
}