#ifndef CHALLENGE_SCREEN_H
#define CHALLENGE_SCREEN_H

#include "../engine/inc/screen.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/field.hpp"
#include "../engine/inc/timer.hpp"

#include "compilerButton.hpp"
#include "aepcompiler.hpp"
#include "programmableObject.hpp"
#include "challenge.hpp"
#include "challengeMap.hpp"
#include "toScreenButton.hpp"
#include "usersManage.hpp"
#include "user.hpp"
#include "dialogBox.hpp"

class ChallengeScreen : public Engine::Screen {
    private:
        ProgrammableObject* player_object = NULL;
        Challenge* challenge = NULL;
        ChallengeMap* map = NULL;
        Engine::Field* console = NULL;
        Engine::TextField* text_field = NULL;
        DialogBox* dialog_box = NULL;
        Engine::Timer* timer = new Engine::Timer();
        std::string player_sprite = "./assets/sprites/bots/bot_a.png";
        std::pair<int, int> map_position = std::make_pair(450, 50);
        std::pair<int, int> text_field_position = std::make_pair(25, 50);
        std::pair<int, int> compiler_button_position = std::make_pair(165,720);
        std::pair<int, int> console_position = std::make_pair(425, 600);
        std::pair<int, int> back_button_position = std::make_pair(25, 15);
        std::pair<int, int> dialog_box_position = std::make_pair(500,300);
        std::pair<std::pair<int, int>,std::pair<int, int>> limits;
        int check_checked_fields = 0;
        std::string console_status;
        User* current_user = NULL;
        void init_map();
        void init_player();
        void init_textfield();
        void init_compiler_objects();
        void init_console();
        void init_back_button();
        void init_current_user();
        void init_dialog_box();
        void show_dialog_box_to_next_map();
        void update_console_initial_info();
        void update_console_running_info();

    public:
        ChallengeScreen(std::string screen_name, Challenge* new_challenge);
        void verify_programmable_object_status();
        void set_player_sprite(std::string path);
        void init();
        void draw();
};

#endif