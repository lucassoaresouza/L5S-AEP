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
    int count = 0;
    for(auto map : maps){
        if(map->get_completed() == false){
            return map;
        }
    }
    return maps[0];
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