#include "../inc/challenge.hpp"

Challenge::Challenge(std::string challenge_title){
    title = challenge_title;
}

int Challenge::get_actual_map_number(){
    int count = 0;
    for(auto map : maps){
        if(map->get_completed() ==  true){
            count++;
        } else {
            return count;
        }
    }
    return count;
}

ChallengeMap* Challenge::get_actual_map(){
    int index = get_actual_map_number();
    std::cout << "Index: " << index << std::endl;
    return maps[index];
}

void Challenge::set_map_complete(int map_index){
    if(maps.size() >= map_index){
        maps[map_index]->set_completed(true);
    }
}

void Challenge::reset_all_maps(){
    for(auto map : maps){
        map->set_completed(false);
    }
}

void Challenge::add_map(ChallengeMap* map){
    maps.push_back(map);
}

std::string Challenge::get_title(){
    return title;
}

bool Challenge::completed(){
    for(auto map : maps){
        if(map->get_completed() == false){
            return false;
        }
    }
    return true;
}

int Challenge::get_maps_count(){
    return maps.size();
}