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
    public:
        ChallengeScreen(std::string screen_name, Challenge* new_challenge);
        void verify_programmable_object_status();
        void init();
        void load();
        void draw();
};

#endif