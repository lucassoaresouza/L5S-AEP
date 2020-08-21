#include <iostream>
#include <string>
#include "game.hpp"
#include "scene.hpp"
#include "gameObject.hpp"


int main(int, char**){

    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);

    std::string object_name="teste";
    std::pair<int, int> object_position(100, 100);

    GameObject* obj_1 = new GameObject(object_name, object_position);

    std::cout << "position x: " << obj_1->get_position_x() << " | position y: " << obj_1->get_position_y() << std::endl;

    Game& game = Game::initialize(game_name, window_size);
    game.run();
    return 0;
}