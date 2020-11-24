#ifndef INIT_USER_BUTTON
#define INIT_USER_BUTTON

#include <iostream>
#include "../engine/inc/button.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/textField.hpp"
#include "selectRobotMenu.hpp"
#include "usersManage.hpp"
#include "user.hpp"

class InitUserButton : public Engine::Button {
    private:
        Engine::TextField* user_input = NULL;

    public:
        InitUserButton(
            std::string object_name,
            std::pair<int,int>object_position,
            std::pair<int,int>object_size
        );
        ~InitUserButton(){};
        void set_user_input(Engine::TextField* input);
        void execute();
};

#endif