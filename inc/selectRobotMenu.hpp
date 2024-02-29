#ifndef SELECT_ROBOT_MENU_H
#define SELECT_ROBOT_MENU_H

#include <iostream>
#include <vector>

#include "../engine/inc/button.hpp"
#include "../engine/inc/field.hpp"
#include "../engine/inc/screen.hpp"
#include "../engine/inc/textField.hpp"
#include "challengeCreator.hpp"
#include "initButton.hpp"
#include "selector.hpp"
#include "user.hpp"
#include "usersManage.hpp"

class SelectRobotMenu : public Engine::Screen {
 private:
  std::pair<int, int> description_position = std::make_pair(345, 160);
  std::pair<int, int> description_2_position = std::make_pair(300, 490);
  std::pair<int, int> operator_name_position = std::make_pair(435, 130);
  std::pair<int, int> next_challenge_button_position = std::make_pair(660, 545);
  std::pair<int, int> back_challenge_button_position = std::make_pair(350, 545);
  std::pair<int, int> challenge_title_position = std::make_pair(430, 530);
  std::pair<int, int> challenge_progress_position = std::make_pair(385, 548);
  std::pair<int, int> selector_field_position = std::make_pair(360, 230);
  std::pair<int, int> robots_position = std::make_pair(330, 200);
  std::pair<int, int> box_position = std::make_pair(300, 25);
  std::pair<int, int> background_position = std::make_pair(330, 200);
  std::pair<int, int> background_position_2 = std::make_pair(330, 530);
  std::pair<int, int> button_position = std::make_pair(470, 630);
  User* current_user = NULL;
  Selector* selector_field = NULL;
  std::vector<Engine::Field*> robots;
  InitButton* init_challenge_button = NULL;
  ChallengeCreator* challenge_creator = NULL;
  Engine::Field* challenge_title = NULL;
  Engine::Field* challenge_progress = NULL;
  Engine::Button* next_challenge_button = NULL;
  Engine::Button* back_challenge_button = NULL;
  std::string challenge_name;
  int next_aux = 0;
  int back_aux = 0;
  int challenge_index = 0;
  void init_selector();
  void init_background();
  void init_texts();
  void init_robots();
  void init_challenge_creator();
  void init_init_button();
  void init_user();
  void init_select_challenge_objects();
  void select_challenge();
  void update_challenge_info();

 public:
  SelectRobotMenu(std::string screen_name);
  void init();
  void draw();
  void to_next_screen();
};

#endif