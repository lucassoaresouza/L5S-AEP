#ifndef TO_SCREEN_BUTTON_H
#define TO_SCREEN_BUTTON_H

#include "../engine/inc/button.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/collider.hpp"
#include "../inc/usersManage.hpp"

class ToScreenButton : public Engine::Button {
    private:
        std::string screen_name;
        bool save_users = false;

    public:
        ToScreenButton(
            std::string object_name,
            std::pair<int,int>object_position,
            std::pair<int,int>object_size,
            bool save
        );
        ~ToScreenButton(){};
        void set_screen_name(std::string name);
        void execute();
};

#endif