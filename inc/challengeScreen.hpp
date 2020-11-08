#ifndef CHALLENGE_SCREEN_H
#define CHALLENGE_SCREEN_H

#include "../engine/inc/screen.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/field.hpp"

#include "compilerButton.hpp"
#include "aepcompiler.hpp"
#include "programmableObject.hpp"
#include "challengeMap.hpp"

class ChallengeScreen : public Engine::Screen {
    public:
        ChallengeScreen(std::string screen_name);
        void init();
        void load();
};

#endif