#ifndef INIT_BUTTON_H
#define INIT_BUTTON_H

#include "../engine/inc/game.hpp"
#include "../engine/inc/button.hpp"
#include "selector.hpp"
#include "challengeCreator.hpp"
#include "challengeScreen.hpp"

class InitButton : public Engine::Button {
    private:
        Selector* selector = NULL;
        std::string challenge_name;
        std::string robot_sprite;
        std::string user_name;
        ChallengeCreator* challenge_creator = NULL;
        ChallengeScreen* new_challenge = NULL;

    public:
        InitButton(
            std::string object_name,
            std::pair<int,int>object_position,
            std::pair<int,int>object_size
        );
        ~InitButton(){};
        void set_selector(Selector* p_selector);
        void set_challenge_creator(ChallengeCreator* p_creator);
        void execute();
};

#endif