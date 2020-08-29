#include <iostream>
#include "../inc/scene.hpp"

using namespace Engine;

Scene::Scene(){};

void Scene::draw(){};
void Scene::load(){};
void Scene::free(){};

void Scene::activate(){
    if(is_active == false){
        is_active = true;
    }
}

void Scene::deactivate(){
    if(is_active == true){
        is_active = false;
    }
}