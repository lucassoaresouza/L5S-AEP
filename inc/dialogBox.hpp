#ifndef DIALOG_BOX_H
#define DIALOG_BOX_H

#include "../engine/inc/gameObject.hpp"
#include "../engine/inc/game.hpp"
#include "../engine/inc/button.hpp"
#include "../engine/inc/field.hpp"

class DialogBox : public Engine::Field {
    private:
        Engine::Field* icon = NULL;
        Engine::Field* text_field = NULL;
        bool active = false;

    public:
        DialogBox(
            std::string name,
            std::pair<int, int> position,
            std::pair<int, int> size
        );
        ~DialogBox(){};
        bool is_active();
        void activate();
        void deactivate();
        void set_icon(
            std::string path,
            std::pair<int, int> obj_position,
            std::pair<int, int> size
        );
        void set_text(
            std::string text,
            std::pair<int, int> obj_position
        );
        bool load();
        void draw();

};

#endif