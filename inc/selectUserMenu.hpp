#ifndef SELECT_USER_MENU_H
#define SELECT_USER_MENU_H

#include <iostream>
#include "../engine/inc/screen.hpp"
#include "../engine/inc/field.hpp"
#include "../engine/inc/textField.hpp"
#include "initUserButton.hpp"

class SelectUserMenu : public Engine::Screen{
    private:
        Engine::Field* label_background = NULL;
        std::pair<int, int> label_background_position = std::make_pair(337,297);
        Engine::Field* title = NULL;
        std::pair<int, int> title_position = std::make_pair(405,310);
        Engine::Field* description = NULL;
        std::pair<int, int> description_position = std::make_pair(365,335);
        Engine::TextField* user_input = NULL;
        std::pair<int, int> user_input_position = std::make_pair(385,400);
        InitUserButton* init_button = NULL;
        std::pair<int, int> init_button_position = std::make_pair(465,480);
        void init_background();
        void init_texts();
        void init_user_input();
        void init_init_button();

    public:
        SelectUserMenu(std::string name);
        ~SelectUserMenu(){};
        void init();

};

#endif