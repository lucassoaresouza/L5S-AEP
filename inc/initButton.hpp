#ifndef INIT_BUTTON_H
#define INIT_BUTTON_H

#include "../engine/inc/button.hpp"
#include "../engine/inc/collider.hpp"
#include "../engine/inc/game.hpp"
#include "challenge.hpp"
#include "challengeCreator.hpp"
#include "challengeScreen.hpp"
#include "selector.hpp"

class InitButton : public Engine::Button {
 private:
  Selector* selector = NULL;
  std::string challenge_name;
  std::string robot_sprite;
  std::string user_name;
  ChallengeCreator* challenge_creator = NULL;
  ChallengeScreen* new_challenge = NULL;
  int user_progress = 0;

 public:
  InitButton(std::string object_name, std::pair<int, int> object_position,
             std::pair<int, int> object_size);
  ~InitButton() {};
  void set_selector(Selector* p_selector);
  void set_challenge_creator(ChallengeCreator* p_creator);
  void execute();
  void set_challenge_info(std::string title, int progress);
};

#endif