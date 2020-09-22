#ifndef COMPILER_BUTTON_H
#define COMPILER_BUTTON_H

#include <iostream>
#include <string>

#include "../engine/inc/button.hpp"
#include "../engine/inc/textField.hpp"
#include "programmableObject.hpp"
#include "aepcompiler.hpp"

class CompilerButton : public Engine::Button{
    private:
        Engine::TextField* text_field = NULL;
        ProgrammableObject* programmable = NULL;
        AEPCompiler* compiler = NULL;

    public:
        CompilerButton(
            std::string object_name,
            std::pair<int,int>object_position,
            std::pair<int,int>object_size
        );
        ~CompilerButton();
        void set_programmable(ProgrammableObject* object_programmable);
        void set_text_field(Engine::TextField* field);
        void set_compiler(AEPCompiler* aep_compiler);
        void execute();
};

#endif