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
            int index_line = 0;
            while(getline(map_file, line)){
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
                        aux_position.first = position.first + i * 32;
                        aux_position.second = position.second + index_line * 32;
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