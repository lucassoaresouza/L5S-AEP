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
}

void ChallengeMap::load_map_info(){
    Engine::Collider& collider = Engine::Collider::get_instance();
    int size_with_spacing = tile_quad_size + spacing;
    std::pair<int,int> aux_position;
    std::pair<int, int> aux_size(
        tile_quad_size,
        tile_quad_size
    );
    std::string grass_path = "./assets/sprites/tiles/grass.png";
    std::string trail_path = "./assets/sprites/tiles/trail.png";
    std::string curve_trail_path = "./assets/sprites/tiles/curve_trail.png";
    std::string plant_path = "./assets/sprites/tiles/plant.png";
    std::string tile_name = "";
    CheckableField* aux_field = NULL;
    int index_line = 0;
    int index_column = 0;
    for(int i = 0; i < map_info.size(); i++){
        tile_name = (std::to_string(index_line));
        aux_position.first = (
            position.first + (index_column + 1) * size_with_spacing
        );
        aux_position.second = (
            position.second + index_line * size_with_spacing
        );
        aux_field = new CheckableField(
            tile_name,
            aux_position,
            aux_size
        );
        switch(map_info[i]){
            case 'G':
                aux_field->set_name("grass");
                aux_field->set_sprite(grass_path, "");
                break;
            case 'V':
                aux_field->set_name("collidable_trail");
                aux_field->set_sprite(trail_path, "");
                aux_field->set_checked_texture(plant_path);
                collider.add_object(aux_field);
                all_checked_field_count += 1;
                break;
            case 'H':
                aux_field->set_name("collidable_trail");
                aux_field->set_sprite(trail_path, "UP-RIGHT");
                aux_field->set_checked_texture(plant_path);
                collider.add_object(aux_field);
                all_checked_field_count += 1;
                break;
            case 'C':
                aux_field->set_name("collidable_trail");
                aux_field->set_sprite(curve_trail_path, "UP-RIGHT");
                aux_field->set_checked_texture(plant_path);
                collider.add_object(aux_field);
                all_checked_field_count += 1;
                break;
            case 'D':
                aux_field->set_name("collidable_trail");
                aux_field->set_sprite(curve_trail_path, "UP-LEFT");
                aux_field->set_checked_texture(plant_path);
                collider.add_object(aux_field);
                all_checked_field_count += 1;
                break;
            case 'E':
                aux_field->set_name("collidable_trail");
                aux_field->set_sprite(curve_trail_path, "DOWN-LEFT");
                aux_field->set_checked_texture(plant_path);
                collider.add_object(aux_field);
                all_checked_field_count += 1;
                break;
            case 'F':
                aux_field->set_name("collidable_trail");
                aux_field->set_sprite(curve_trail_path, "DOWN-RIGHT");
                aux_field->set_checked_texture(plant_path);
                collider.add_object(aux_field);
                all_checked_field_count += 1;
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

    CheckableField* background_field = new CheckableField(
        "background_field",
        background_position,
        background_size
    );
    background_field->set_color(0x555, 0x555, 0x555, 0x00);
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
        CheckableField* border_line_field = new CheckableField(
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
        border_line_field->set_sprite("./assets/sprites/tiles/border.png", "");
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
        CheckableField* border_column_field = new CheckableField(
            "border_field",
            border_position,
            std::pair<int,int>(tile_quad_size,tile_quad_size)
        );
        border_column_field->set_bold(true);
        border_column_field->set_font("./assets/fonts/larabiefont-rg.ttf", 15);
        border_column_field->set_text(std::to_string(i+1));
        border_column_field->set_color(color.r, color.g, color.b, color.a);
        border_column_field->set_sprite(
            "./assets/sprites/tiles/border.png",
            ""
        );
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
    obj_initial_position.first = x;
    obj_initial_position.second = y;
}

std::pair<int,int> ChallengeMap::get_possible_position(int x, int y){
    return possible_positions[x][y];
}

bool ChallengeMap::verify_all_trail_checked(){
    for(auto tile : tiles){
        if(tile->get_name() == "collidable_trail"){
            if(tile->is_checked() == false){
                return false;
            }
        }
    }
    return true;
}

void ChallengeMap::reset_all_trail_checks(){
    for(auto tile : tiles){
        if(tile->get_name() == "collidable_trail"){
            tile->uncheck();
        }
    }
}

std::pair<int, int> ChallengeMap::get_obj_initial_position(){
    return get_possible_position(
        obj_initial_position.first,
        obj_initial_position.second
    );
}

void ChallengeMap::init(){
    add_background();
    add_table_border();
    load_map_info();
}

std::string ChallengeMap::get_text_info(){
    return text_info;
}

int ChallengeMap::get_all_checked_field_count(){
    return all_checked_field_count;
}

int ChallengeMap::get_checked_field_count(){
    int count = 0;
    for(CheckableField* tile : tiles){
        if(tile->is_checked()==true){
            count +=1;
        }
    }
    return count;
}

void ChallengeMap::free(){
    if(texture){
        SDL_DestroyTexture(texture);
    }
    for(auto tile : tiles){
        tile->free();
    }
}