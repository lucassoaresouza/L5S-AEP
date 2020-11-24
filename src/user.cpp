#include "../inc/user.hpp"

User::User(std::string username){
    name = username;
}

void User::set_challenge(std::string name, int done, int total){
    std::pair<std::string, std::pair<int, int>> challenge;
    challenge = std::make_pair(
        name,
        std::make_pair(done,total)
    );
    challenges.push_back(challenge);
}

std::pair<int, int> User::get_challenge_progress(std::string name){
    for(auto challenge : challenges){
        if(challenge.first == name){
            return challenge.second;
        }
    }
    return std::make_pair(0,0);
}

std::string User::get_name(){
    return name;
}