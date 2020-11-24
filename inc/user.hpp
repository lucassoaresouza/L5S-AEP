#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "challenge.hpp"

class User {
    private:
        std::string name;
        std::vector<std::pair<std::string, std::pair<int, int>>> challenges;

    public:
        User(std::string username);
        ~User(){};
        void set_challenge(std::string name, int done, int total);
        std::pair<int, int> get_challenge_progress(std::string name);
        std::string get_name();

};

#endif