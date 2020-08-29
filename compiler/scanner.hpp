#ifndef SCANNER_H
#define SCANNER_H

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Compiler_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL Compiler::Parser::symbol_type Compiler::Scanner::get_next_token()

#include "parser.hpp"

namespace Compiler {
    class Interpreter;
    class Scanner : public yyFlexLexer {
        private:
            Interpreter &m_driver;

        public:
            Scanner(Interpreter &driver) : m_driver(driver) {}
            virtual ~Scanner(){}
            virtual Compiler::Parser::symbol_type get_next_token();
    };
}

#endif