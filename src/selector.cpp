#include "../inc/selector.hpp"

using namespace Engine;

Selector::Selector(
            std::string name,
            std::pair<int, int> position,
            std::pair<int, int> size,
            int count_lines,
            int count_columns,
            int count_displacement
){
    set_name(name);
    set_position(position);
    set_size(size);
    lines = count_lines;
    columns = count_columns;
    displacement = count_displacement;
    limit_x.first = position.first;
    limit_x.second = position.first + ((columns - 1) * displacement);
    limit_y.first = position.second;
    limit_y.second = position.second + ((lines -1 )* displacement);
    for(int i = 0; i < lines; i++){
        for(int j = 0; j < columns; j++){
            possible_positions.push_back(std::make_pair(
                    position.first + (j * displacement),
                    position.second + (i * displacement)
                )
            );
        }
    }
}

void Selector::add_position(std::pair<int, int> position){
    possible_positions.push_back(position);
}

void Selector::set_new_position_mouse(int x, int y){
    std::pair<int, int> aux_position = std::make_pair(2000,2000);
    for(auto p : possible_positions){
        int aux_x = abs(p.first - x);
        int aux_y = abs(p.second - y);
        if(aux_x < abs(aux_position.first - x)){
            aux_position.first = p.first;
        }
        if(aux_y < abs(aux_position.second - y)){
            aux_position.second = p.second;
        }
    }
    position.first = aux_position.first;
    position.second = aux_position.second;
}

void Selector::read_input(SDL_Event *event){
    if(event->type == SDL_KEYDOWN){
        switch (event->key.keysym.sym){
            case SDLK_UP:
                if(position.second > limit_y.first){
                    position.second -= displacement;
                } else {
                    position.second = limit_y.second;
                }
                break;
            case SDLK_DOWN:
                if(position.second < limit_y.second){
                    position.second += displacement;
                } else {
                    position.second = limit_y.first;
                }
                break;
            case SDLK_LEFT:
                if(position.first > limit_x.first){
                    position.first -= displacement;
                } else {
                    position.first = limit_x.second;
                }
                break;
            case SDLK_RIGHT:
                if(position.first < limit_x.second){
                    position.first += displacement;
                } else {
                    position.first = limit_x.first;
                }
                break;
            default:
                break;
        }
    } else if(event->type == SDL_MOUSEBUTTONDOWN){
        int x;
        int y;
        SDL_GetMouseState( &x, &y);
        if(
            x >= limit_x.first &&
            x <= limit_x.second + displacement &&
            y >= limit_y.first &&
            y <= limit_y.second + displacement
        ){
            set_new_position_mouse(x,y);
        }
    }
}



