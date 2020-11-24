#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
        ~UsersManage(){};
        User* get_user(std::string name);
        void add_user(User* user);
        void set_current_user(User* user);
};

#endif