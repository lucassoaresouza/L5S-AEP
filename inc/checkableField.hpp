#ifndef CHECKABLE_FIELD_H
#define CHECKABLE_FIELD_H

#include "../engine/inc/field.hpp"

class CheckableField : public Engine::Field {
    private:
        bool checked = false;

    public:
        CheckableField(
            std::string object_name,
            std::pair<int, int> object_position,
            std::pair<int, int> object_size
        );
        void check();
        void uncheck();
        bool is_checked();
        void collide();
};

#endif