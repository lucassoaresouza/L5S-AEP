#ifndef CHECKABLE_FIELD_H
#define CHECKABLE_FIELD_H

#include "../engine/inc/field.hpp"
#include "../engine/inc/game.hpp"

class CheckableField : public Engine::Field {
    private:
        bool checked = false;
        std::string checked_texutre_path;
        SDL_Texture* checked_texture = NULL;

    public:
        CheckableField(
            std::string object_name,
            std::pair<int, int> object_position,
            std::pair<int, int> object_size
        );
        void set_checked_texture(std::string path);
        void check();
        void uncheck();
        bool is_checked();
        void collide();
        void draw();
};

#endif