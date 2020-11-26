#ifndef CHALLENGE_SCREEN_H
#define CHALLENGE_SCREEN_H

#include "../engine/inc/screen.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/field.hpp"

#include "compilerButton.hpp"
#include "aepcompiler.hpp"
#include "programmableObject.hpp"
#include "challenge.hpp"
#include "challengeMap.hpp"


class ChallengeScreen : public Engine::Screen {
    private:
        ProgrammableObject* player_object = NULL;
        Challenge* challenge = NULL;
        ChallengeMap* map = NULL;
        Engine::Field* console = NULL;
        Engine::TextField* text_field = NULL;
        std::string player_sprite = "./assets/sprites/bots/bot_a.png";
        std::pair<int, int> map_position = std::make_pair(450, 50);
        std::pair<int, int> text_field_position = std::make_pair(25, 50);
        std::pair<int, int> compiler_button_position = std::make_pair(165,720);
        std::pair<int, int> console_position = std::make_pair(425, 600);
        std::pair<std::pair<int, int>,std::pair<int, int>> limits;
        void init_map();
        void init_player();
        void init_textfield();
        void init_compiler_objects();
        void init_console();


    public:
        ChallengeScreen(std::string screen_name, Challenge* new_challenge);
        void verify_programmable_object_status();
        void set_player_sprite(std::string path);
        void init();
        void draw();
};

#endif