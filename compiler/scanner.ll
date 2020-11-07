%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.hpp"
	#include "interpreter.hpp"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;

	#define yyterminate() Compiler::Parser::make_END(Compiler::location());

	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Compiler_"

%%

sigaNorte   { 
                return Compiler::Parser::make_NORTH(Compiler::location()); 
            }

sigaSul { 
                return Compiler::Parser::make_SOUTH(Compiler::location()); 
            }

sigaLeste   { 
                return Compiler::Parser::make_EAST(Compiler::location()); 
            }

sigaOeste   { 
                return Compiler::Parser::make_WEST(Compiler::location()); 
            }

ativar      {
                return Compiler::Parser::make_ACTIVATE(Compiler::location());
            }

VDD         {
                return Compiler::Parser::make_TRUE(Compiler::location());
            }

FLS         {
                return Compiler::Parser::make_FALSE(Compiler::location());
            }

e           {
                return Compiler::Parser::make_AND(Compiler::location());
            }

ou          {
                return Compiler::Parser::make_OR(Compiler::location());
            }

se          {
                return Compiler::Parser::make_IF(Compiler::location());
            }

senao       {
                return Compiler::Parser::make_ELSE(Compiler::location());
            }

repita      {
                return Compiler::Parser::make_REPEAT(Compiler::location());
            }

=           {
                return Compiler::Parser::make_ASSIGNER(Compiler::location());
            }

==          {
                return Compiler::Parser::make_EQUAL(Compiler::location());
            }

\>          {
                return Compiler::Parser::make_GREATER(Compiler::location());
            }

\>=         {
                return Compiler::Parser::make_GREATEREQUAL(Compiler::location());
            }

\<=         {
                return Compiler::Parser::make_LESSEQUAL(Compiler::location());
            }

\<          {
                return Compiler::Parser::make_LESS(Compiler::location());
            }

\*\*        {
                return Compiler::Parser::make_POWERSYM(Compiler::location());
            }

\*          {
                return Compiler::Parser::make_MULTSYM(Compiler::location());
            }

\/          {
                return Compiler::Parser::make_DIVSYM(Compiler::location());
            }

\+          {
                return Compiler::Parser::make_SUMSYM(Compiler::location());
            }

\-          {
                return Compiler::Parser::make_SUBSYM(Compiler::location());
            }

[a-z_A-Z]+  {
                return Compiler::Parser::make_STRING(yytext, Compiler::location());
            }

\(          {
                return Compiler::Parser::make_LEFTPAR(Compiler::location());
            }

\)          {
                return Compiler::Parser::make_RIGHTPAR(Compiler::location());
            }

\{          {
                return Compiler::Parser::make_LEFTBRACE(Compiler::location());
            }

\}          {
                return Compiler::Parser::make_RIGHTBRACE(Compiler::location());
            }

,           {
                return Compiler::Parser::make_COMMA(Compiler::location());
            }

;           {
                return Compiler::Parser::make_SEMICOLON(Compiler::location());
            }

\n          {
                return Compiler::Parser::make_EOL(Compiler::location());
            }


[\t ]     {}

[0-9]* {
                int number = atoi(yytext);
                return Compiler::Parser::make_INTEGER(number, Compiler::location());
            }

[0-9]+"."[0-9]+ {
    double number = atof(yytext);
    return Compiler::Parser::make_DOUBLE(number, Compiler::location());
}

.           {}

<<EOF>>     { return yyterminate(); }


%%
