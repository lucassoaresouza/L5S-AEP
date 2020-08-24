#include "log.hpp"


void Log::print(std::string message){
    std::cout << message << std::endl;
}

void Log::print(std::string message, bool save){
    if(save){
        std::ofstream myfile("./log/log_file.txt", std::ios::app);
        myfile << "[LOG]" << message << "\n";
        myfile.close();
    } else {    
        std::cout << message << std::endl;
    }
}