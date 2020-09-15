#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../engine/inc/game.hpp"
#include "../engine/inc/scene.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/log.hpp"

#include "../compiler/interpreter.hpp"
#include "../compiler/command.hpp"
#include "aepcompiler.hpp"

using namespace Engine;
using namespace Compiler;
using namespace std;

int main(int, char**){
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);
    Game& game = Game::initialize(game_name, window_size);

    std::string object_name="teste";
    std::pair<int, int> object_position(800, 100);
    std::pair<int, int> object_size(67, 56);

    GameObject* obj_1 = new GameObject(object_name, object_position, object_size);
    obj_1->set_sprite("./assets/bots/B-25c.png");
    game.add_object(obj_1);

    game.load_objects();
    game.run();

    // AEPCompiler* compiler = new AEPCompiler();
    // std::string test = "";
    // cin >> test;
    // compiler->run(test);

    return 0;
}