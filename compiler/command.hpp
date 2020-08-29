#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include <stdint.h>

namespace Compiler {
    class Command{
        private:
            std::string m_name;
            std::vector<uint64_t> m_args;
        public:
            Command(const std::string &name, const std::vector<uint64_t> arguments);
            Command(const std::string &name);
            Command();
            ~Command();

            std::string str() const;
            std::string name() const;
    };
}

#endif