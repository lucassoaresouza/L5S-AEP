#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iostream>

namespace Engine {
class Log {
 public:
  static void print(std::string message);
  static void print(std::string message, bool save);
};
}  // namespace Engine

#endif