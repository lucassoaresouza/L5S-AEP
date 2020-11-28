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

%token <std::string> STRING  "string";
%token <uint64_t> INTEGER "inteiro";
%token <double> DOUBLE "decimal";
%token RIGHTBRACE "chave \'{\'";
%token LEFTBRACE "chave \'}\'";
%token RIGHTPAR "parentese \'(\'";
%token LEFTPAR "parentese \')\'";
%token END 0 "fim do arquivo";
%token EOL "fim da linha";
%token COMMA "virgula \',\'";
%token SEMICOLON "ponto e virgula \';\'";

%token POWERSYM MULTSYM DIVSYM SUMSYM SUBSYM ASSIGNER;
%token LESS GREATER EQUAL GREATEREQUAL LESSEQUAL;
%token NORTH SOUTH WEST EAST ACTIVATE;
%token IF ELSE REPEAT;
%token TRUE FALSE;
%token AND OR;

%type <Compiler::Node*> atomexpr powexpr unaryexpr mulexpr addexpr expr;
%type <Compiler::Node*> constant boolean variable;
%type <Compiler::Node*> boolexp logicalexp;
%type <Compiler::Node*> block;
%type <Compiler::Node*> ifblock repeatblock;
%type <Compiler::Node*> command;
%type <std::vector<Compiler::Node*>> context;
%type <Compiler::Node*> assignment;
%type <Compiler::Node*> ifexpression;

%start start

%%

start       : program;

program     : context EOL {
                driver.manage->nodes = $1;
            };

context     : {
                std::vector<Compiler::Node*> context;
                $$ = context;
            };
            | context EOL {
                $$ = $1;
            };
            | context assignment SEMICOLON{
                $1.push_back($2);
                $$ = $1;
            };
            | context expr SEMICOLON {
                $1.push_back($2);
                $$ = $1;
            };
            | context logicalexp SEMICOLON {
                $1.push_back($2);
                $$ = $1;
            };
            | context ifblock {
                $1.push_back($2);
                $$ = $1;
            };
            | context repeatblock {
                $1.push_back($2);
                $$ = $1;
            };
            | context command SEMICOLON {
                $1.push_back($2);
                $$ = $1;
            }

block   : LEFTBRACE context RIGHTBRACE {
            NodeBlock* node  = new NodeBlock();
            node->nodes = $2;
            $$ = node;
        };

ifexpression    : boolexp {
                    $$ = $1;
                };
                | boolean {
                    $$ = $1;
                };
                | logicalexp {
                    $$ = $1;
                };
                | variable {
                    $$ = $1;
                };

ifblock     : IF LEFTPAR ifexpression RIGHTPAR block {
                NodeIf* node = new NodeIf($3, $5);
                $$ = node;
            };
            | IF LEFTPAR ifexpression RIGHTPAR block ELSE block{
                NodeIf* node = new NodeIf($3, $5, $7);
                $$ = node;
            };

repeatblock     : REPEAT LEFTPAR expr RIGHTPAR block {
                    NodeRepeat* node = new NodeRepeat($3, $5);
                    $$ = node;
                };

command     : NORTH LEFTPAR expr RIGHTPAR {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeCommand($3, "NORTH", manage);
            };
            | EAST LEFTPAR expr RIGHTPAR {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeCommand($3, "EAST", manage);
            };
            | WEST LEFTPAR expr RIGHTPAR {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeCommand($3, "WEST", manage);
            };
            | SOUTH LEFTPAR expr RIGHTPAR {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeCommand($3, "SOUTH", manage);
            };
            | ACTIVATE LEFTPAR RIGHTPAR {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeCommand("ACTIVATE", manage);
            }

constant    : INTEGER {
                $$ = new NodeConst($1);
            };
            | DOUBLE {
                $$ = new NodeConst($1);
            };

boolean     : TRUE {
                $$ = new NodeBool(true);
            };
            | FALSE {
                $$ = new NodeBool(false);
            };

variable    : STRING {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeVariable($1, manage);
            };

assignment  : STRING ASSIGNER expr {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeAssignment($1, $3, manage);
            };
            | STRING ASSIGNER logicalexp {
                TreeManage* manage = driver.get_manage();
                $$ = new NodeAssignment($1, $3, manage);
            };

atomexpr    : variable {
                $$ = $1;
            };
            | constant {
                $$ = $1;
            };
            | boolean {
                $$ = $1;
            };
            | LEFTPAR expr RIGHTPAR {
                $$ = $2;
            };

powexpr     : atomexpr {
                $$ = $1;
            };
            | atomexpr POWERSYM powexpr {
                $$ = new NodeCalc($1, $3, '^');
            };

unaryexpr   : powexpr {
                $$ = $1;
            };
            | SUMSYM powexpr {
                $$ = $2;
            };
            | SUBSYM powexpr {
                $$ = new NodeNegate($2);
            };

mulexpr     : unaryexpr {
                $$ = $1;
            };
            | mulexpr MULTSYM unaryexpr {
                $$ = new NodeCalc($1, $3, '*');
            };
            | mulexpr DIVSYM unaryexpr {
                $$ = new NodeCalc($1, $3, '/');
            };

addexpr     : mulexpr {
                $$ = $1;
            };
            | boolexp {
                $$ = $1;
            };
            | addexpr SUMSYM mulexpr {
                    $$ = new NodeCalc($1, $3, '+');
            };
            | addexpr SUBSYM mulexpr {
                    $$ = new NodeCalc($1, $3, '-');
            };

expr        : addexpr {
                $$ = $1;
            };

boolexp     : atomexpr OR atomexpr {
                $$ =  new NodeLogical($1, $3, "||");
            };
            | atomexpr AND atomexpr {
                $$ =  new NodeLogical($1, $3, "&&");
            };

logicalexp  : expr LESS expr {
                $$ =  new NodeLogical($1, $3, "<");
            };
            | expr GREATER expr {
                $$ =  new NodeLogical($1, $3, ">");
            };
            | expr EQUAL expr {
                $$ =  new NodeLogical($1, $3, "==");
            };
            | expr GREATEREQUAL expr {
                $$ =  new NodeLogical($1, $3, ">=");
            };
            | expr LESSEQUAL expr {
                $$ =  new NodeLogical($1, $3, "<=");
            };
%%

// Bison expects us to provide implementation - otherwise linker complains
void Compiler::Parser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl;
    driver.clear();
}

