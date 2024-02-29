#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "user.hpp"

class UsersManage {
 private:
  static UsersManage* instance;
  std::vector<User*> users;
  User* current_user = NULL;
  std::string user_file_path;
  void read_users();
  UsersManage(std::string path);

 public:
  static UsersManage& get_instance();
  ~UsersManage() {};
  User* get_user(std::string name);
  void add_user(User* user);
  void set_current_user(User* user);
  User* get_current_user();
  void save_users_status();
};

#endif