#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>

class Log{
    public:
        static void print(std::string message);
        static void print(std::string message, bool save);
};

#endif