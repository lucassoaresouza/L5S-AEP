%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.hpp"
	#include "interpreter.hpp"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;

	#define yyterminate() L5SCompiler::Parser::make_END(L5SCompiler::location());

	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="L5SCompiler_"

%%


[a-z]+      { 
                cout << "Scanner: identifier [" << yytext << "]" << endl;
                return L5SCompiler::Parser::make_STRING(yytext, L5SCompiler::location( /* put location data here if you want */ )); 
            }
            
\(          {
                cout << "Scanner: '('" << endl;
                return L5SCompiler::Parser::make_LEFTPAR(L5SCompiler::location());
            }
            
\)          { 
                cout << "Scanner: ')'" << endl;
                return L5SCompiler::Parser::make_RIGHTPAR(L5SCompiler::location());
            }
            
;           {
                cout << "Scanner: ';'" << endl;
                return L5SCompiler::Parser::make_SEMICOLON(L5SCompiler::location());
            }
            
,           {
                cout << "Scanner: ','" << endl;
                return L5SCompiler::Parser::make_COMMA(L5SCompiler::location());
            }
            
[\n\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[1-9][0-9]* {
                cout << "Scanner: decimal number: " << yytext << endl;
                uint64_t number = strtoull(yytext, 0, 10);
                return L5SCompiler::Parser::make_NUMBER(number, L5SCompiler::location());
            }

.           { 
                cout << "Scanner: unknown character [" << yytext << "]" << endl; 
            }
            
<<EOF>>     { return yyterminate(); }


%%
