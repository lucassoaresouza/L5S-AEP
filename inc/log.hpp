#ifndef LOG_H
#define LOG_H

#include <iostream>

class Log{
    public:
        Log(){};
        static void print(std::string message);
};

#endif