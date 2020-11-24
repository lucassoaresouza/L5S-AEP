#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../engine/inc/game.hpp"
#include "../inc/challengeCreator.hpp"
#include "../inc/challengeScreen.hpp"
#include "../inc/selectRobotMenu.hpp"


using namespace Engine;

int main(int, char**){
    //Game initialization
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);
    Game& game = Game::initialize(game_name, window_size);
    
    
    //Screen
    SelectRobotMenu* select_robot = new SelectRobotMenu("select_robot");

    ChallengeCreator* c_creator = new ChallengeCreator();
    c_creator->create_maps("./levels");

    //Screen Desafio-1
    ChallengeScreen* screen = new ChallengeScreen(
        "desafio-1",
        c_creator->get_challenge_by_title("challenge_a.aep")
    );

    //Run
    game.add_screen(screen);
    game.add_screen(select_robot);
    game.load_screen("select_robot");
    game.run();
    return 0;
}
