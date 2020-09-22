#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../engine/inc/game.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/button.hpp"
#include "../inc/compilerButton.hpp"

#include "../compiler/interpreter.hpp"
#include "../compiler/command.hpp"
#include "aepcompiler.hpp"
#include "programmableObject.hpp"

using namespace Engine;
using namespace Compiler;
using namespace std;

int main(int, char**){
    //game
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);
    Game& game = Game::initialize(game_name, window_size);

    //aviao
    std::string object_name="aviao";
    std::pair<int, int> object_position(700, 450);
    std::pair<int, int> object_size(67, 56);
    ProgrammableObject* obj_1 = new ProgrammableObject(
        object_name,
        object_position,
        object_size
    );
    obj_1->set_sprite("./assets/bots/B-25c.png");
    game.add_object(obj_1);

    //textfield
    std::string object_name2="textfield";
    std::pair<int, int> object_position2(500, 300);
    std::pair<int, int> object_size2(67, 56);
    TextField* obj_2 = new TextField(object_name2, object_position2, 40, 40);
    obj_2->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    obj_2->set_color(0x00, 0x00, 0x00, 0x00);
    game.add_object(obj_2);

    //compiler
    AEPCompiler* compiler = new AEPCompiler();
    // std::string test = "";
    // test = obj_2->get_current_text();
    // compiler->run(test);

    //button
    std::string button_name = "button";
    std::pair<int, int> button_position(400,600);
    std::pair<int, int> button_size(128,64);
    CompilerButton* button = new CompilerButton(button_name, button_position, button_size);
    button->set_sprites(
        "./assets/buttons/button1.png",
        "./assets/buttons/button2.png"
    );
    button->set_compiler(compiler);
    button->set_programmable(obj_1);
    button->set_text_field(obj_2);
    game.add_object(button);

    //load and run!
    game.load_objects();
    game.run();


    return 0;
}