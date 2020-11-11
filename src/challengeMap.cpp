#include "../inc/challengeMap.hpp"

ChallengeMap::ChallengeMap(
    std::string map_name,
    std::pair<int, int>position,
    std::string path
){
    set_name(map_name);
    set_position(position);
    map_path = path;
    read_file();
}

bool ChallengeMap::read_file(){
    std::string line;
    std::ifstream map_file(map_path);
    if(map_file.is_open()){
        getline(map_file, line);
        std::istringstream iss(line);
        if(line != "" && line[0] != '#'){
            iss >> columns;
            iss >> lines;
            iss >> spacing;
            add_background(columns, lines, spacing);
            add_table_border(columns, lines, spacing);
            int index_line = 0;
            while(getline(map_file, line)){
                int size_with_spacing = 32 + spacing;
                if(line != "" && line[0] != '#'){
                    std::pair<int,int> aux_position;
                    std::pair<int, int> aux_size(32,32);
                    std::string grass_path = "./assets/tiles/grass.png";
                    std::string trail_path = "./assets/tiles/trail.png";
                    std::string tile_name = "";
                    Engine::Field* aux_field = NULL;
                    for(int i = 0; i < columns; i++){
                        tile_name += (
                            "tile_" +
                            std::to_string(index_line) +
                            "_" +
                            std::to_string(i)
                        );
                        aux_position.first = (
                            position.first + (i + 1) * size_with_spacing
                        );
                        aux_position.second = (
                            position.second + index_line * size_with_spacing
                        );
                        aux_field = new Engine::Field(
                            tile_name,
                            aux_position,
                            aux_size
                        );
                        switch(line[i]){
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
                    }
                    index_line += 1;
                }
            }
        }
        return true;
    } else {
        Engine::Log().print("Arquivo de desafio nao encontrado!");
        return false;
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

void ChallengeMap::add_background(int columns, int lines, int spacing){
    int size_with_spacing = 32 + spacing;
    columns += 1;
    lines += 1;
    std::pair<int, int> background_size(
        (columns * size_with_spacing) + spacing,
        (lines * size_with_spacing) + spacing
    );

    std::pair<int, int> background_position(position.first - spacing, position.second - spacing);

    Engine::Field* background_field = new Engine::Field(
        "background_field",
        background_position,
        background_size
    );
    background_field->set_color(0x0, 0x0, 0x0, 0x0);
    tiles.push_back(background_field);
}

void ChallengeMap::add_table_border(int columns, int lines, int spacing){

    //Add border lines
    std::pair<int, int> border_position(position.first, position.second);
    for(int i = 0; i < lines ; i++){
        border_position.second = position.second + i * 33;
        Engine::Field* border_line_field = new Engine::Field(
            "border_field",
            border_position,
            std::pair<int,int>(32,32)
        );
        border_line_field->set_color(0xFFF, 0xFFF, 0xFFF, 0xFFF);
        tiles.push_back(border_line_field);
    }

    //Add border columns
    border_position.first = position.first;
    border_position.second =  2 + position.second * (lines + (32 + spacing));
    for(int i = 0; i < columns ; i++){
        border_position.first = position.first + (i + 1) * (32 + spacing);
        Engine::Field* border_column_field = new Engine::Field(
            "border_field",
            border_position,
            std::pair<int,int>(32,32)
        );
        border_column_field->set_color(0xFFF, 0xFFF, 0xFFF, 0xFFF);
        tiles.push_back(border_column_field);
    }

}