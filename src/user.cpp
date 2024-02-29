#include "../inc/user.hpp"

User::User(std::string username) { name = username; }

void User::set_challenge(std::string title, int done) {
  std::pair<std::string, int> challenge;
  challenge = std::make_pair(title, done);
  challenges.push_back(challenge);
}

int User::get_challenge_progress(std::string challenge_title) {
  int index = search_challenge_progresss(challenge_title);
  if (index >= 0) {
    return challenges[index].second;
  } else {
    return 0;
  }
}

std::string User::get_name() { return name; }

void User::set_map_progress(std::string challenge_title) {
  int index = search_challenge_progresss(challenge_title);
  if (index >= 0) {
    challenges[index].second++;
  } else {
    challenges.push_back(std::make_pair(challenge_title, 1));
  }
}

std::vector<std::pair<std::string, int>> User::get_all_challenges() {
  return challenges;
}

int User::search_challenge_progresss(std::string challenge_title) {
  int count = 0;
  for (auto challenge : challenges) {
    if (challenge.first == challenge_title) {
      return count;
    } else {
      count++;
    }
  }
  return -1;
}