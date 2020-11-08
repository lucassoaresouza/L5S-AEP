#include "../inc/screenManage.hpp"

using namespace Engine;

void ScreenManage::add_screen(Screen* screen){
    screens.push_back(screen);
}

Screen* ScreenManage::get_screen(std::string screen_name){
    for(auto screen : screens){
        if(screen->get_name() == screen_name){
            return screen;
        }
    }
    Log().print("Screen not found!");
    return NULL;
}