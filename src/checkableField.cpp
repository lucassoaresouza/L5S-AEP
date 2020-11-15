#include "../inc/checkableField.hpp"

CheckableField::CheckableField(
    std::string object_name,
    std::pair<int, int> object_position,
    std::pair<int, int> object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
}

void CheckableField::check(){
    std::cout << "aquiiii!!" << std::endl;
    checked = true;
}

void CheckableField::uncheck(){
    checked = false;
}

bool CheckableField::is_checked(){
    return checked;
}

void CheckableField::collide(){
    check();
}

