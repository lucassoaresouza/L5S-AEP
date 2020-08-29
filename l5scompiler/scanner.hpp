#ifndef SCANNER_H
#define SCANNER_H

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer L5SCompiler_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL L5SCompiler::Parser::symbol_type L5SCompiler::Scanner::get_next_token()

#include "parser.hpp"

namespace L5SCompiler {
    class Interpreter;
    class Scanner : public yyFlexLexer {
        private:
            Interpreter &m_driver;

        public:
            Scanner(Interpreter &driver) : m_driver(driver) {}
            virtual ~Scanner(){}
            virtual L5SCompiler::Parser::symbol_type get_next_token();
    };
}

#endif