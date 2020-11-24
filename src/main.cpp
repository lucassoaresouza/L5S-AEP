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

    game.add_screen(select_robot);
    game.load_screen("select_robot");
    game.run();
    return 0;
}
