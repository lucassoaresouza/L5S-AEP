#ifndef CHALLENGE_H
#define CHALLENGE_H

#include <vector>
#include "challengeMap.hpp"

class Challenge {
    private:
        std::string title;
        std::vector<ChallengeMap*> maps;

    public:
        Challenge(std::string challenge_title);
        ~Challenge();
        ChallengeMap* get_actual_map();
        int get_actual_map_number();
        void set_map_complete(int map_index);
        void reset_all_maps();
        void add_map(ChallengeMap* map);
        std::string get_title();
};

#endif