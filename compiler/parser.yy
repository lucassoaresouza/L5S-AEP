%skeleton "lalr1.cc"
%require "3.0"
%defines
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { Compiler }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "command.hpp"
    #include "syntaticTree.hpp"

    using namespace std;

    namespace Compiler {
        class Scanner;
        class Interpreter;
    }
}

%code top
{
    #include <iostream>
    #include "scanner.hpp"
    #include "parser.hpp"
    #include "interpreter.hpp"
    #include "location.hh"

    static Compiler::Parser::symbol_type yylex(Compiler::Scanner &scanner, Compiler::Interpreter &driver) {
        return scanner.get_next_token();
    }

    using namespace Compiler;
}

%lex-param { Compiler::Scanner &scanner }
%lex-param { Compiler::Interpreter &driver }
%parse-param { Compiler::Scanner &scanner }
%parse-param { Compiler::Interpreter &driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file";
%token EOL "end of line";
%token <std::string> STRING  "string";
%token <uint64_t> INTEGER "integer";
%token <double> DOUBLE "double";
%token LEFTPAR "leftpar";
%token RIGHTPAR "rightpar";
%token LEFTBRACE "leftbrace";
%token RIGHTBRACE "rightbrace";
%token COMMA "comma";

%token <std::string> NORTH;
%token <std::string> SOUTH;
%token <std::string> EAST;
%token <std::string> WEST;

%token <std::string> TRUE;
%token <std::string> FALSE;
%token <std::string> AND;
%token <std::string> OR;
%token <std::string> IF;
%token <std::string> ASSIGNER;

%type< Compiler::Command > command;
%type< Compiler::Command > reservedCommand;
%type< std::vector<Compiler::Command> > commandBlock;
%type< std::vector<uint64_t> > arguments;
%type< bool > booleanOperation;
%type< bool > decisionBlock;
%type< bool > boolean;

%type <Compiler::Node*> constant;


%start program

%%

program     : { driver.clear(); }
            | program command {
                const Command &cmd = $2;
                driver.addCommand(cmd);
            }
            | program reservedCommand {
                const Command &cmd = $2;
                driver.addCommand(cmd);
            }
            | program assignment {}
            | program booleanOperation {}
            | program commandBlock {}
            | program decisionBlock {}
            | program constant {}

commandBlock : LEFTBRACE program RIGHTBRACE {}

decisionBlock: IF LEFTPAR booleanOperation RIGHTPAR commandBlock {}

command : STRING LEFTPAR RIGHTPAR
        {
            string &id = $1;
            $$ = Command(id);
        }
    | STRING LEFTPAR arguments RIGHTPAR
        {
            string &id = $1;
            const std::vector<uint64_t> &args = $3;
            $$ = Command(id, args);
        }
    ;

reservedCommand : NORTH LEFTPAR INTEGER RIGHTPAR
                {
                    string id = "NORTH";
                    const uint64_t &number = $3;
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                | SOUTH LEFTPAR INTEGER RIGHTPAR
                {
                    string id = "SOUTH";
                    const uint64_t &number = $3;
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                | EAST LEFTPAR INTEGER RIGHTPAR
                {
                    string id = "EAST";
                    const uint64_t &number = $3;
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                | WEST LEFTPAR INTEGER RIGHTPAR
                {
                    string id = "WEST";
                    const uint64_t &number = $3;
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                 ;

arguments : INTEGER
        {
            uint64_t number = $1;
            $$ = std::vector<uint64_t>();
            $$.push_back(number);
        }
    | arguments COMMA INTEGER
        {
            uint64_t number = $3;
            std::vector<uint64_t> &args = $1;
            args.push_back(number);
            $$ = args;
        }
    ;

boolean : TRUE
        {
            bool value = true;
            $$ = value;
        }
        | FALSE
        {
            bool value = false;
            $$ = value;
        }

booleanOperation : boolean
        {
            bool value = $1;
            $$ = value;
        }
        | boolean AND booleanOperation
        {
            bool value = $1 && $3;
            $$ = value;
        }
        | boolean OR booleanOperation
        {
            bool value = $1 || $3;
            $$ = value;
        }

constant    : INTEGER {
                std::cout << "CONSTANTE INTEIRA :" << $1 << std::endl;
                $$ = new Compiler::NodeConst($1);
            }
            | DOUBLE {
                std::cout << "CONSTANTE DECIMAL :" << $1 << std::endl;
                $$ = new Compiler::NodeConst($1);
            }


assignment  : STRING ASSIGNER constant {
                std::cout << "nome: " << $1 << " valor: " << $3->evaluate() << std::endl;
                delete $3;
            }

%%

// Bison expects us to provide implementation - otherwise linker complains
void Compiler::Parser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
    driver.clear();
}