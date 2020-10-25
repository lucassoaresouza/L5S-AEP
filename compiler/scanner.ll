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
                // cout << "Scanner: identifier [" << yytext << "]" << endl;
                return Compiler::Parser::make_NORTH(yytext, Compiler::location()); 
            }

sigaSul     { 
                // cout << "Scanner: identifier [" << yytext << "]" << endl;
                return Compiler::Parser::make_SOUTH(yytext, Compiler::location()); 
            }

sigaLeste   { 
                // cout << "Scanner: identifier [" << yytext << "]" << endl;
                return Compiler::Parser::make_EAST(yytext, Compiler::location()); 
            }

sigaOeste   { 
                // cout << "Scanner: identifier [" << yytext << "]" << endl;
                return Compiler::Parser::make_WEST(yytext, Compiler::location()); 
            }

verdadeiro  {
                return Compiler::Parser::make_TRUE(yytext, Compiler::location());
            }

falso       {
                return Compiler::Parser::make_FALSE(yytext, Compiler::location());
            }

e           {
                return Compiler::Parser::make_AND(yytext, Compiler::location());
            }

ou          {
                return Compiler::Parser::make_OR(yytext, Compiler::location());
            }

se          {
                return Compiler::Parser::make_IF(yytext, Compiler::location());
            }

=           {
                return Compiler::Parser::make_ASSIGNER(yytext, Compiler::location());
            }

\^          {
                return Compiler::Parser::make_POWERSYM(yytext, Compiler::location());
            }

\*          {
                return Compiler::Parser::make_MULTSYM(yytext, Compiler::location());
            }

\/          {
                return Compiler::Parser::make_DIVSYM(yytext, Compiler::location());
            }

\+          {
                return Compiler::Parser::make_SUMSYM(yytext, Compiler::location());
            }

\-          {
                return Compiler::Parser::make_SUBSYM(yytext, Compiler::location());
            }

[a-z_A-Z]+  {
                // cout << "Scanner: identifier [" << yytext << "]" << endl;
                return Compiler::Parser::make_STRING(yytext, Compiler::location());
            }

\(          {
                // cout << "Scanner: '('" << endl;
                return Compiler::Parser::make_LEFTPAR(Compiler::location());
            }

\)          {
                // cout << "Scanner: ')'" << endl;
                return Compiler::Parser::make_RIGHTPAR(Compiler::location());
            }

\{          {
                // cout << "Scanner: '('" << endl;
                return Compiler::Parser::make_LEFTBRACE(Compiler::location());
            }

\}          {
                // cout << "Scanner: ')'" << endl;
                return Compiler::Parser::make_RIGHTBRACE(Compiler::location());
            }

,           {
                // cout << "Scanner: ','" << endl;
                return Compiler::Parser::make_COMMA(Compiler::location());
            }

[\n\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[1-9][0-9]* {
                // cout << "Scanner: decimal number: " << yytext << endl;
                int number = atoi(yytext);
                return Compiler::Parser::make_INTEGER(number, Compiler::location());
            }

[0-9]+"."[0-9]+ {
    double number = atof(yytext);
    return Compiler::Parser::make_DOUBLE(number, Compiler::location());
}

.           {
                // cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }

<<EOF>>     { return yyterminate(); }


%%
