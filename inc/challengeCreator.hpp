#ifndef CHALLENGE_CREATOR_H
#define CHALLENGE_CREATOR_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "challenge.hpp"
#include "challengeMap.hpp"

class ChallengeCreator {
 private:
  std::string challenge_paths;
  DIR *dir;
  struct dirent *lsdir;
  std::vector<std::string> file_paths;
  std::vector<Challenge *> challenges;
  std::vector<std::string> challenge_titles;
  void get_files();
  void read_files();
  void read_folder();

 public:
  ChallengeCreator() {};
  ~ChallengeCreator() {};
  void create_maps(std::string folder);
  std::vector<Challenge *> get_all_challenges();
  Challenge *get_challenge_by_title(std::string name);
  std::string get_challenge_title(int index);
  int get_challenge_count();
  int get_challenge_maps_count(std::string name);
};

#endif