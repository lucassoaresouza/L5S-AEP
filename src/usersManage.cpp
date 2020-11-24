#include "../inc/usersManage.hpp"

UsersManage* UsersManage::instance = NULL;

UsersManage& UsersManage::get_instance(){
    if(!instance){
        std::string default_path = "./data/users/users.aep";
        instance = new UsersManage(default_path);
        return *instance;
    } else {
        return *instance;
    }
}

UsersManage::UsersManage(std::string path){
    user_file_path = path;
    read_users();
}

void UsersManage::read_users(){
    std::string line;
    std::string username;
    std::string challenge_string;
    std::ifstream file(user_file_path);
    if(file.is_open()){
        while(getline(file, line)){
            if(line[0] != '#'){
                if(line == "init"){
                    getline(file, username);
                    User* new_user = new User(username);
                    do{
                        getline(file, line);
                        if(line != "end"){
                            std::string name;
                            int done, total;
                            std::istringstream iss(line);
                            iss >> name;
                            iss >> done;
                            iss >> total;
                            new_user->set_challenge(name, done, total);
                        } else {
                            users.push_back(new_user);
                        }
                    } while(line != "end");
                }
            }
        }
    }
    file.close();
}

User* UsersManage::get_user(std::string name){
    for(User* user : users){
        if(user->get_name() == name){
            return user;
        }
    }
    return NULL;
}

void UsersManage::add_user(User* user){
    users.push_back(user);
}

void UsersManage::set_current_user(User* user){
    current_user = user;
}