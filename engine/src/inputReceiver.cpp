#include "../inc/inputReceiver.hpp"

using namespace Engine;

InputReceiver* InputReceiver::instance = NULL;

InputReceiver& InputReceiver::get_instance(){
    if(!instance){
        instance = new InputReceiver();
        return *instance;
    } else {
        return *instance;
    }
}

void InputReceiver::run(){
    SDL_Event e;
    SDL_StartTextInput();
    while(SDL_PollEvent(&e) != 0){
        event = e;
        std::cout << e.type << std::endl;
    }
    SDL_StopTextInput();
}

SDL_Event* InputReceiver::get_last_input(){
    return &event;
}

void InputReceiver::registry_observer(GameObject* observer){
    observers.push_back(observer);
}
