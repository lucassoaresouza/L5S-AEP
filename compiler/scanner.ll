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

,           {
                // cout << "Scanner: ','" << endl;
                return Compiler::Parser::make_COMMA(Compiler::location());
            }
            
[\n\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[1-9][0-9]* {
                // cout << "Scanner: decimal number: " << yytext << endl;
                uint64_t number = strtoull(yytext, 0, 10);
                return Compiler::Parser::make_NUMBER(number, Compiler::location());
            }

.           { 
                // cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }
            
<<EOF>>     { return yyterminate(); }


%%
