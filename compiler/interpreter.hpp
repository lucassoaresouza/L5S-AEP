#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include "scanner.hpp"
#include "parser.hpp"
#include "syntaticTree.hpp"

namespace Compiler {

    class Command;

    class Interpreter{
        private:
            Scanner m_scanner;
            Parser m_parser;
            std::vector<Command> m_commands;
            TreeManage* manage = NULL;
            unsigned int m_location;
            void increaseLocation(unsigned int loc);
            unsigned int location() const;

        public:
            Interpreter();
            int parse();
            void clear();
            TreeManage* get_manage();
            std::string str() const;
            void switchInputStream(std::istream *is);
            command_list get_commands();
            friend class Parser;
            friend class Scanner;
        
    };
}

#endif