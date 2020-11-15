#include "../inc/challengeMap.hpp"

ChallengeMap::ChallengeMap(
    std::string map_name,
    std::pair<int, int>position,
    std::string info,
    std::string text
){
    set_name(map_name);
    set_position(position);
    completed = false;
    map_info = info;
    text_info = text;
    add_background();
    add_table_border();
    load_map_info();
}

void ChallengeMap::load_map_info(){
    int size_with_spacing = tile_quad_size + spacing;
    std::pair<int,int> aux_position;
    std::pair<int, int> aux_size(
        tile_quad_size,
        tile_quad_size
    );
    std::string grass_path = "./assets/tiles/grass.png";
    std::string trail_path = "./assets/tiles/trail.png";
    std::string tile_name = "";
    Engine::Field* aux_field = NULL;
    int index_line = 0;
    int index_column = 0;
    for(int i = 0; i < map_info.size(); i++){
        tile_name += (
            "tile_" +
            std::to_string(index_line) +
            "_" +
            std::to_string(i)
        );
        aux_position.first = (
            position.first + (index_column + 1) * size_with_spacing
        );
        aux_position.second = (
            position.second + index_line * size_with_spacing
        );
        aux_field = new Engine::Field(
            tile_name,
            aux_position,
            aux_size
        );
        switch(map_info[i]){
            case 'G':
                aux_field->set_sprite(grass_path);
                break;
            case 'T':
                aux_field->set_sprite(trail_path);
                break;
            default:
                break;
        }
        tiles.push_back(aux_field);
        possible_positions[index_column][index_line] = aux_position;
        index_column += 1;
        if(index_column == columns - 1){
            index_column = 0;
            index_line += 1;
        }
    }
}

bool ChallengeMap::load(){
    for(auto tile : tiles){
        tile->load();
    }
    return true;
}

void ChallengeMap::draw(){
    for(auto tile : tiles){
        tile->draw();
    }
}

void ChallengeMap::add_background(){
    int size_with_spacing = tile_quad_size + spacing;
    columns += 1;
    lines += 1;
    std::pair<int, int> background_size(
        (columns * size_with_spacing) + spacing,
        (lines * size_with_spacing) + spacing
    );

    std::pair<int, int> background_position(
        position.first - spacing, position.second - spacing
    );

    Engine::Field* background_field = new Engine::Field(
        "background_field",
        background_position,
        background_size
    );
    background_field->set_color(0x0, 0x0, 0x0, 0x0);
    tiles.push_back(background_field);
}

void ChallengeMap::add_table_border(){
    line_border();
    column_border();
}

void ChallengeMap::line_border(){
    SDL_Color color = {0x0, 0x0, 0x0, 0x0};
    std::pair<int, int> border_position(
        position.first, position.second
    );
    char letter_a_index = 65;
    std::string aux_string;
    char aux_index = letter_a_index;
    for(int i = 0; i < lines-1 ; i++){
        border_position.second = position.second + i * 33;
        Engine::Field* border_line_field = new Engine::Field(
            "border_field",
            border_position,
            std::pair<int,int>(tile_quad_size,tile_quad_size)
        );
        aux_string = "";
        aux_index = letter_a_index + i;
        border_line_field->set_bold(true);
        border_line_field->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
        border_line_field->set_text(aux_string + aux_index);
        border_line_field->set_color(color.r, color.g, color.b, color.a);
        border_line_field->set_sprite("./assets/tiles/border.png");
        tiles.push_back(border_line_field);
    }
}

void ChallengeMap::column_border(){
    SDL_Color color = {0x0, 0x0, 0x0, 0x0};
    std::pair<int, int> border_position(
        position.first, position.second
    );
    border_position.first = position.first;
    border_position.second = (
        position.second + ((lines-1) * (tile_quad_size+spacing))
    );
    for(int i = 0; i < columns-1; i++){
        border_position.first = (
            position.first + (i + 1) * (tile_quad_size + spacing)
        );
        Engine::Field* border_column_field = new Engine::Field(
            "border_field",
            border_position,
            std::pair<int,int>(tile_quad_size,tile_quad_size)
        );
        border_column_field->set_bold(true);
        border_column_field->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
        border_column_field->set_text(std::to_string(i+1));
        border_column_field->set_color(color.r, color.g, color.b, color.a);
        border_column_field->set_sprite("./assets/tiles/border.png");
        tiles.push_back(border_column_field);
    }
}

std::pair<std::pair<int, int>,std::pair<int, int>> ChallengeMap::get_limits(){
    std::pair<std::pair<int, int>,std::pair<int, int>> limits;
    limits.first = std::make_pair(
        position.first + tile_quad_size,
        position.second
    );
    limits.second = std::make_pair(
        position.first + (tile_quad_size * columns),
        position.second + (tile_quad_size * (lines - 1))
    );
    return limits;
}

void ChallengeMap::set_completed(bool status){
    completed = status;
}

bool ChallengeMap::get_completed(){
    return completed;
}

void ChallengeMap::set_obj_initial_position(int x, int y){
    obj_inital_position.first = x;
    obj_inital_position.first = y;
}

std::pair<int,int> ChallengeMap::get_possible_position(int x, int y){
    return possible_positions[x][y];
}