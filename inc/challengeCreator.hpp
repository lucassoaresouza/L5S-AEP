#ifndef CHALLENGE_CREATOR_H
#define CHALLENGE_CREATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "challengeMap.hpp"
#include "challenge.hpp"

class ChallengeCreator {
    private:
        std::string challenge_paths;
        DIR *dir;
        struct dirent *lsdir;
        std::vector<std::string> file_paths;
        std::vector<Challenge*> challenges;
        void get_files();
        void read_files();
        void read_folder();

    public:
        ChallengeCreator(){};
        ~ChallengeCreator(){};
        void create_maps(std::string folder);
        std::vector<Challenge*> get_all_challenges();
        Challenge* get_challenge_by_title(std::string name);
};

#endif