#ifndef SELECT_USER_MENU_H
#define SELECT_USER_MENU_H

#include "../engine/inc/screen.hpp"
#include "../engine/inc/field.hpp"
#include "../engine/inc/textField.hpp"

class SelectUserMenu : public Engine::Screen{
    private:
        Engine::Field* label_background = NULL;
        std::pair<int, int> label_bacground_position = std::make_pair(10,10);
        Engine::Field* title = NULL;
        std::pair<int, int> title_position = std::make_pair(10,10);
        Engine::TextField* user_input = NULL;
        std::pair<int, int> user_input_position = std::make_pair(10,10);

    public:
        void init();
        void load();

};

#endif