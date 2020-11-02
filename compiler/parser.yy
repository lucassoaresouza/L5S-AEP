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
%token <uint64_t> INTEGER "integer";
%token <double> DOUBLE "double";
%token RIGHTBRACE "rightbrace";
%token LEFTBRACE "leftbrace";
%token RIGHTPAR "rightpar";
%token END 0 "end of file";
%token EOL "end of line";
%token LEFTPAR "leftpar";
%token COMMA "comma";

%token POWERSYM MULTSYM DIVSYM SUMSYM SUBSYM ASSIGNER;
%token LESS GREATER EQUAL GREATEREQUAL LESSEQUAL;
%token NORTH SOUTH WEST EAST;
%token IF ELSE REPEAT;
%token TRUE FALSE;
%token AND OR;

%type< Compiler::Command > reservedCommand;
%type< std::vector<uint64_t> > arguments;
%type< Compiler::Command > command;

%type <Compiler::Node*> atomexpr powexpr unaryexpr mulexpr addexpr expr;
%type <Compiler::Node*> constant boolean variable;
%type <Compiler::Node*> boolexp logicalexp;

%start program

%%

program     : { driver.clear(); }
            | program command EOL{
                const Command &cmd = $2;
                driver.addCommand(cmd);
            }
            | program reservedCommand EOL{
                const Command &cmd = $2;
                driver.addCommand(cmd);
            }
            | program assignment EOL;
            | program expr EOL{
                driver.manage->nodes.push_back($2);
            }
            | program logicalexp EOL{
                driver.manage->nodes.push_back($2);
            }

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

constant    : INTEGER {
                $$ = new Compiler::NodeConst($1);
            }
            | DOUBLE {
                $$ = new Compiler::NodeConst($1);
            }

boolean     : TRUE {
                $$ = new Compiler::NodeBool(true);
            }
            | FALSE {
                $$ = new Compiler::NodeBool(false);
            }

variable    : STRING {
                if(driver.manage->existsVariable($1)){
                    Node* t = driver.manage->getVariable($1);
                    $$ = driver.manage->getVariable($1);
                } else {
                    std::cout << "Erro: Variavel '" << $1 << "' nao encontrada!!!" << std::endl;
                    YYERROR;
                }
            }

assignment  : STRING ASSIGNER expr {
                driver.manage->variables[$1] = $3;
            }
            | STRING ASSIGNER logicalexp {
                driver.manage->variables[$1] = $3;
            }

atomexpr    : variable {
                $$ = $1;
            }
            | constant {
                $$ = $1;
            }
            | boolean {
                $$ = $1;
            }
            | LEFTPAR expr RIGHTPAR {
                $$ = $2;
            }

powexpr     : atomexpr {
                $$ = $1;
            }
            | atomexpr POWERSYM powexpr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    $$ = new NodeCalc($1, $3, '^');
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }

unaryexpr   : powexpr {
                $$ = $1;
            }
            | SUMSYM powexpr {
                $$ = $2;
            }
            | SUBSYM powexpr {
                if($2->type() == 'N'){
                    $$ = new NodeNegate($2);
                } else if($2->type() == 'B'){
                    $$ = new NodeBool(!$2->evaluate());
                }
            }

mulexpr     : unaryexpr {
                $$ = $1;
            }
            | mulexpr MULTSYM unaryexpr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    $$ = new NodeCalc($1, $3, '*');
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }
            | mulexpr DIVSYM unaryexpr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    $$ = new NodeCalc($1, $3, '/');
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }

addexpr     : mulexpr {
                $$ = $1;
            }
            | boolexp {
                $$ = $1;
            }
            | addexpr SUMSYM mulexpr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    $$ = new NodeCalc($1, $3, '+');
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }
            | addexpr SUBSYM mulexpr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    $$ = new NodeCalc($1, $3, '-');
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }

expr        : addexpr {
                $$ = $1;
            }

boolexp     : atomexpr OR atomexpr {
                if($1->type() == 'B' && $3->type() == 'B'){
                    bool value = $1->evaluate() || $3->evaluate();
                    $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }
            | atomexpr AND atomexpr {
                if($1->type() == 'B' && $3->type() == 'B'){
                    bool value = $1->evaluate() && $3->evaluate();
                    $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar operacao entre bool e nro" << std::endl;
                    YYERROR;
                }
            }

logicalexp  : expr LESS expr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    bool value = $1->evaluate() < $3->evaluate();
                    $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar comparacao entre bool e nro" << std::endl;
                    YYERROR;
                }    
            }
            | expr GREATER expr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    bool value = $1->evaluate() > $3->evaluate();
                    $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar comparacao entre bool e nro" << std::endl;
                    YYERROR;
                }      
            }
            | expr EQUAL expr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    bool value = $1->evaluate() == $3->evaluate();
                    $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar comparacao entre bool e nro" << std::endl;
                    YYERROR;
                }   
            }
            | expr GREATEREQUAL expr {
                if($1->type() == 'N' && $3->type() == 'N'){
                    bool value = $1->evaluate() >= $3->evaluate();
                    $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar comparacao entre bool e nro" << std::endl;
                    YYERROR;
                }  
            }
            | expr LESSEQUAL expr {
                if($1->type() == 'N' && $3->type() == 'N'){
                bool value = $1->evaluate() <= $3->evaluate();
                $$ = new NodeBool(value);
                } else {
                    std::cout << "Erro: Nao eh possivel realizar comparacao entre bool e nro" << std::endl;
                    YYERROR;
                } 
            }
%%

// Bison expects us to provide implementation - otherwise linker complains
void Compiler::Parser::error(const location &loc , const std::string &message) {
    cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
    driver.clear();
}

