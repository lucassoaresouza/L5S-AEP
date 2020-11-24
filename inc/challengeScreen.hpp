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
        std::string player_sprite = "./assets/sprites/bots/bot_a.png";
        std::pair<int, int> map_position = std::make_pair(450, 50);
        std::pair<int, int> text_field_position = std::make_pair(25, 50);
        std::pair<int, int> compiler_button_position = std::make_pair(135,690);
        std::pair<int, int> console_position = std::make_pair(425, 600);
    public:
        ChallengeScreen(std::string screen_name, Challenge* new_challenge);
        void verify_programmable_object_status();
        void set_player_sprite(std::string path);
        void init();
        void draw();
};

#endif