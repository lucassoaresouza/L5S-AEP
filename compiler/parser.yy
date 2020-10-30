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

%token <std::string> POWERSYM MULTSYM DIVSYM SUMSYM SUBSYM ASSIGNER;
%token <std::string> NORTH SOUTH WEST EAST;
%token <std::string> TRUE FALSE;
%token <std::string> AND OR;
%token <std::string> IF;

%type< Compiler::Command > command;
%type< Compiler::Command > reservedCommand;
%type< std::vector<Compiler::Command> > commandBlock;
%type< std::vector<uint64_t> > arguments;
%type< bool > booleanOperation;
%type< bool > decisionBlock;
%type< bool > boolean;

%type <Compiler::Node*> constant variable;
%type <Compiler::Node*> atomexpr powexpr unaryexpr mulexpr addexpr expr;


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
            | program booleanOperation {}
            | program commandBlock {}
            | program decisionBlock {}
            | program assignment {}
            | program expr {
                driver.manage->nodes.push_back($2);
            }
            | program expr END {
                driver.manage->nodes.push_back($2);
            }

commandBlock : LEFTBRACE program RIGHTBRACE {}

decisionBlock: IF LEFTPAR booleanOperation RIGHTPAR commandBlock {}

command     : STRING LEFTPAR RIGHTPAR {
                string &id = $1;
                $$ = Command(id);
            }
            | STRING LEFTPAR arguments RIGHTPAR {
                string &id = $1;
                const std::vector<uint64_t> &args = $3;
                $$ = Command(id, args);
            }

reservedCommand : NORTH LEFTPAR expr RIGHTPAR
                {
                    string id = "NORTH";
                    const uint64_t &number = $3->evaluate();
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                | SOUTH LEFTPAR expr RIGHTPAR
                {
                    string id = "SOUTH";
                    const uint64_t &number = $3->evaluate();
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                | EAST LEFTPAR expr RIGHTPAR
                {
                    string id = "EAST";
                    const uint64_t &number = $3->evaluate();
                    std::vector<uint64_t>arguments;
                    arguments.push_back(number);
                    $$ = Command(id, arguments);
                }
                | WEST LEFTPAR expr RIGHTPAR
                {
                    string id = "WEST";
                    const uint64_t &number = $3->evaluate();
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
                $$ = new Compiler::NodeConst($1);
            }
            | DOUBLE {
                $$ = new Compiler::NodeConst($1);
            }

variable    : STRING {
                if(!driver.manage->existsVariable($1)){
                    YYERROR;
                } else {
                    $$ = new NodeConst(driver.manage->getVariable($1));
                }
            }

assignment  : STRING ASSIGNER expr {
                driver.manage->variables[$1] = $3->evaluate();
                delete $3;
            }

atomexpr    : constant {
                $$ = $1;
            }
            | variable {
                $$ = $1;
            }
            | LEFTPAR expr RIGHTPAR {
                $$ = $2;
            }

powexpr     : atomexpr {
                $$ = $1;
            }
            | atomexpr POWERSYM powexpr {
                $$ = new NodeCalc($1, $3, '^');
            }

unaryexpr   : powexpr {
                $$ = $1;
            }
            | SUMSYM powexpr {
                $$ = $2;
            }
            | SUBSYM powexpr {
                $$ = new NodeNegate($2);
            }

mulexpr     : unaryexpr {
                $$ = $1;
            }
            | mulexpr MULTSYM unaryexpr {
                $$ = new NodeCalc($1, $3, '*');
            }
            | mulexpr DIVSYM unaryexpr {
                $$ = new NodeCalc($1, $3, '/');
            }

addexpr     : mulexpr {
                $$ = $1;
            }
            | addexpr SUMSYM mulexpr {
                $$ = new NodeCalc($1, $3, '+');
            }
            | addexpr SUBSYM mulexpr {
                $$ = new NodeCalc($1, $3, '-');
            }

expr        : addexpr {
                $$ = $1;
            }

%%

// Bison expects us to provide implementation - otherwise linker complains
void Compiler::Parser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
    driver.clear();
}
