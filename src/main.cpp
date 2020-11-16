#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../engine/inc/game.hpp"
#include "../inc/challengeCreator.hpp"
#include "../inc/challengeScreen.hpp"


using namespace Engine;

int main(int, char**){
    //Game initialization
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);
    Game& game = Game::initialize(game_name, window_size);
    
    ChallengeCreator* c_creator = new ChallengeCreator();
    c_creator->create_maps("./levels");

    //Test screen
    ChallengeScreen* screen = new ChallengeScreen(
        "screenTeste",
        c_creator->get_challenge_by_title("challenge_a.aep")
    );

    //Run
    game.add_screen(screen);
    game.load_screen(screen->get_name());
    game.run();
    return 0;
}
