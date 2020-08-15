#include <iostream>
#include <string>
#include "game.hpp"

int main(int, char**){

    std::string game_name="AEP";
    std::pair<int,int> window_size(800,600);

    Game& game = Game::initialize(game_name, window_size);
    game.run();
    return 0;
}