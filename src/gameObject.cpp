#include <iostream>
#include "gameObject.hpp"


GameObject::GameObject(){};

GameObject::GameObject(
    std::string object_name,
    std::pair<int, int> object_position
){
    name = object_name;
    position = object_position;
}

void GameObject::set_position(std::pair <int, int> object_position){
    position = object_position;
};
void GameObject::set_name(std::string object_name){
    name = object_name;
};
void GameObject::set_size(std::pair<int, int> object_size){
    size = object_size;
};

std::pair<int, int> GameObject::get_position(){
    return position;
};
int GameObject::get_position_x(){
    return position.first;
};
int GameObject::get_position_y(){
    return position.second;
};

std::pair<int, int> GameObject::get_size(){
    return size;
};
int GameObject::get_width(){
    return size.first;
};
int GameObject::get_height(){
    return size.second;
};


void GameObject::set_sprite(std::string path){
    sprite = path;
}
void GabeObject::load_sprite(){
    if(sprite){
        std::cout << "BOA! TEM SPRITE!" << std::endl;
        std::cout << sprite << std::endl;
    } else {
        std::cout << "Sprite nao encontrada!"
    }
}
