#include "../inc/collider.hpp"

using namespace Engine;

Collider* Collider::instance = NULL;

Collider& Collider::get_instance(){
    if(!instance){
        instance = new Collider();
        return *instance;
    } else {
        return *instance;
    }
}

void Collider::add_object(GameObject* object){
    objects.push_back(object);
}

std::vector<GameObject*> Collider::verify(GameObject* object){
    std::vector<GameObject*> collisions;
    collisions.clear();
    for(auto collidable_object : objects){
        std::pair<int, int> object_position = object->get_position();
        std::pair<int, int> collidable_position = (
            collidable_object->get_position()
        );
        if(
            object != collidable_object &&
            object_position.first >= collidable_position.first - 3 &&
            object_position.first <= collidable_position.first + 3 &&
            object_position.second >= collidable_position.second - 3 &&
            object_position.second <= collidable_position.second + 3 
        ){
            collisions.push_back(collidable_object);
        }
    }
    return collisions;
}

void Collider::remove_all_objects(){
    objects.clear();
}