#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../engine/inc/game.hpp"
#include "../engine/inc/textField.hpp"
#include "../engine/inc/button.hpp"
#include "../engine/inc/field.hpp"
#include "../engine/inc/screen.hpp"

#include "../compiler/interpreter.hpp"
#include "../compiler/command.hpp"

#include "compilerButton.hpp"
#include "aepcompiler.hpp"
#include "programmableObject.hpp"
#include "challengeMap.hpp"


#include "../compiler/syntaticTree.hpp"

using namespace Engine;
using namespace Compiler;
using namespace std;

int main(int, char**){
    //game
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);
    Game& game = Game::initialize(game_name, window_size);
    
    //screen
    Screen* screen = new Screen("teste-1");

    //field
    std::string map_name="map";
    std::pair<int, int> map_posititon(405, 10);
    std::string map_path = "./levels/level_one/challenge_a.aep";
    // std::pair<int, int> field_size(19*32, 15*32);
    ChallengeMap* map = new ChallengeMap(map_name, map_posititon, map_path);
    // field->set_color(0xFF, 0xFF, 0xFF, 0xFF);

    //console field
    std::string console_name="console";
    std::pair<int, int> console_posititon(405, ((15*32)+15));
    std::pair<int, int> console_size(19*32, 181);
    Field* console = new Field(console_name, console_posititon, console_size);
    console->set_color(0x99, 0x99, 0x99, 0x99);

    //aviao
    std::string object_name="aviao";
    std::pair<int, int> object_position(700, 450);
    std::pair<int, int> object_size(32, 32);
    ProgrammableObject* obj_1 = new ProgrammableObject(
        object_name,
        object_position,
        object_size
    );
    obj_1->set_sprite("./assets/bots/B-25c.png");

    //textfield
    std::string object_name2="textfield";
    std::pair<int, int> object_position2(10, 10);
    TextField* obj_2 = new TextField(object_name2, object_position2, 35, 40);
    obj_2->set_font( "./assets/fonts/larabiefont-rg.ttf", 15);
    obj_2->set_font_color(0x00, 0x00, 0x00, 0x00);

    //compiler
    AEPCompiler* compiler = new AEPCompiler();

    //button
    std::string button_name = "button";
    std::pair<int, int> button_position(120,660);
    std::pair<int, int> button_size(128,64);
    CompilerButton* button = new CompilerButton(button_name, button_position, button_size);
    button->set_sprites(
        "./assets/buttons/button1.png",
        "./assets/buttons/button2.png"
    );
    button->set_compiler(compiler);
    button->set_programmable(obj_1);
    button->set_text_field(obj_2);

    //load and run!
    screen->add_object(map);
    screen->add_object(obj_1);
    screen->add_object(obj_2);
    screen->add_object(console);
    screen->add_object(button);
    game.add_screen(screen);
    game.load_screen(screen->get_name());
    game.run();
    return 0;
}