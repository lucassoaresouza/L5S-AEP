#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../engine/inc/game.hpp"
#include "../engine/inc/scene.hpp"
#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/log.hpp"
#include "../engine/inc/inputReceiver.hpp"

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

    std::string object_name2="teste2";
    std::pair<int, int> object_position2(500, 300);
    std::pair<int, int> object_size2(67, 56);
    TextField* obj_2 = new TextField(object_name2, object_position2, 40, 40);
    obj_2->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    obj_2->set_color(0x00, 0x00, 0x00, 0x00);
    game.add_object(obj_2);
    game.load_objects();
    game.run();

    AEPCompiler* compiler = new AEPCompiler();
    std::string test = "";
    test = obj_2->get_current_text();
    compiler->run(test);

    return 0;
}