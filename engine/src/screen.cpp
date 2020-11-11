#include "../inc/screen.hpp"

using namespace Engine;

Screen::Screen(){
    name = "default";
}

Screen::Screen(std::string screen_name){
    name = screen_name;
}

void Screen::set_name(std::string screen_name){
    name = screen_name;
}

std::string Screen::get_name(){
    return name;
}

void Screen::add_object(GameObject* object){
    objects.push_back(object);
    input_receiver.register_observer(object);
}

void Screen::load(){
    for(auto object : objects){
        object->load();
    }
}

void Screen::draw(){
    for(auto object : objects){
        object->draw();
    }
}