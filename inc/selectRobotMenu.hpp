#ifndef SELECT_ROBOT_MENU_H
#define SELECT_ROBOT_MENU_H

#include <iostream>
#include <vector>

#include "../engine/inc/screen.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/field.hpp"
#include "challengeCreator.hpp"
#include "initButton.hpp"
#include "selector.hpp"
#include "usersManage.hpp"
#include "user.hpp"

class SelectRobotMenu : public Engine::Screen {
    private:
        Selector* selector_field = NULL;
        std::pair<int, int> selector_field_position = std::make_pair(360,260);
        Engine::Field* background_field = NULL;
        std::pair<int, int> background_position = std::make_pair(330,230);
        std::pair<int, int> robots_position = std::make_pair(330,230);
        std::vector<Engine::Field*> robots;
        InitButton* init_challenge_button = NULL;
        std::pair<int, int> button_position = std::make_pair(480,495);
        ChallengeCreator* challenge_creator = NULL;
        User* current_user = NULL;
        std::pair<int, int> select_bot_position = std::make_pair(355,190);
        std::pair<int, int> operator_name_position = std::make_pair(485,160);
        void init_selector();
        void init_background();
        void init_texts();
        void init_robots();
        void init_challenge_creator();
        void init_init_button();
        void init_user();

    public:
        SelectRobotMenu(std::string screen_name);
        void init();
        void to_next_screen();
};

#endif