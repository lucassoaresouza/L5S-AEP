#include "../inc/user.hpp"

User::User(std::string username){
    name = username;
}

void User::set_challenge(std::string title, int done){
    std::pair<std::string, int> challenge;
    challenge = std::make_pair(
        title,
        done
    );
    challenges.push_back(challenge);
}

int User::get_challenge_progress(std::string challenge_title){
    for(auto challenge : challenges){
        if(challenge.first == challenge_title){
            return challenge.second;
        }
    }
    return 0;
}

std::string User::get_name(){
    return name;
}

void User::set_map_progress(std::string challenge_title){
    for(int i = 0; i < challenges.size(); i++){
        if(challenges[i].first == challenge_title){
            challenges[i].second++;
        }
    }
}