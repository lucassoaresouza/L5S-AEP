#include <iostream>
#include <string>
#include "game.hpp"
#include "scene.hpp"
#include "gameObject.hpp"
#include "log.hpp"
#include <string>

int main(int, char**){
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);

    std::string object_name="teste";
    std::pair<int, int> object_position(100, 100);
    Game& game = Game::initialize(game_name, window_size);

    GameObject* obj_1 = new GameObject(object_name, object_position);
    obj_1->set_sprite("./assets/bots/B-25c.png");
    game.add_object(obj_1);
    game.load_objects();
    game.run();
    return 0;
}