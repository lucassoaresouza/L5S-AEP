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


[a-z]+      { 
                cout << "Scanner: identifier [" << yytext << "]" << endl;
                return Compiler::Parser::make_STRING(yytext, Compiler::location( /* put location data here if you want */ )); 
            }
            
\(          {
                cout << "Scanner: '('" << endl;
                return Compiler::Parser::make_LEFTPAR(Compiler::location());
            }
            
\)          { 
                cout << "Scanner: ')'" << endl;
                return Compiler::Parser::make_RIGHTPAR(Compiler::location());
            }
            
;           {
                cout << "Scanner: ';'" << endl;
                return Compiler::Parser::make_SEMICOLON(Compiler::location());
            }
            
,           {
                cout << "Scanner: ','" << endl;
                return Compiler::Parser::make_COMMA(Compiler::location());
            }
            
[\n\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[1-9][0-9]* {
                cout << "Scanner: decimal number: " << yytext << endl;
                uint64_t number = strtoull(yytext, 0, 10);
                return Compiler::Parser::make_NUMBER(number, Compiler::location());
            }

.           { 
                cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }
            
<<EOF>>     { return yyterminate(); }


%%
