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
#include "challengeScreen.hpp"


#include "../compiler/syntaticTree.hpp"

using namespace Engine;
using namespace Compiler;
using namespace std;

int main(int, char**){
    //Game initialization
    std::string game_name="AEP";
    std::pair<int,int> window_size(1024,768);
    Game& game = Game::initialize(game_name, window_size);
    
    //Test screen
    ChallengeScreen* screen = new ChallengeScreen("screenTeste");

    //Run
    game.add_screen(screen);
    game.load_screen(screen->get_name());
    game.run();
    return 0;
}

// #include <iostream>
// #include "../inc/challengeCreator.hpp"

// int main(){
//     ChallengeCreator* c_creator = new ChallengeCreator();
//     c_creator->create_maps("./levels");
//     return 0;
// }