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
}

void Screen::add_object_with_input(GameObject* object){
    objects.push_back(object);
    input_receiver.register_observer(object);
}

void Screen::load(){
    init();
    for(auto object : objects){
        object->load();
    }
}

void Screen::draw(){
    for(auto object : objects){
        object->draw();
    }
}

void Screen::remove_all_objects(){
    objects.clear();
    for(auto object : objects){
        input_receiver.unregister_observer(
            object->get_name()
        );
    }
}

void Screen::free(){
    for(auto object : objects){
        object->free();
    }
    remove_all_objects();
}