#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "challenge.hpp"

class User {
    private:
        std::string name;
        std::vector<std::pair<std::string, int>> challenges;
        int index = 0;

    public:
        User(std::string username);
        ~User(){};
        void set_challenge(std::string title, int done);
        int get_challenge_progress(std::string challenge_title);
        std::string get_name();
        void set_map_progress(std::string challenge_name);
        std::vector<std::pair<std::string, int>> get_all_challenges();
        int search_challenge_progresss(std::string challenge_title);

};

#endif