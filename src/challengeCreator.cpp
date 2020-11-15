#include "../inc/challengeCreator.hpp"

// std::vector<ChallengeMap*> ChallengeCreator::create_maps(std::string folder){
void ChallengeCreator::create_maps(std::string folder){
    challenge_paths = folder;
    read_folder();
    read_files();
}

void ChallengeCreator::read_folder(){
    dir = opendir(challenge_paths.c_str());
    if(dir != NULL){
        std::string delimiter = "/";
        while( (lsdir = readdir(dir)) != NULL ){
            // std::cout << lsdir->d_name << std::endl;
            std::string aux_string;
            aux_string = "";
            std::string file_std_string = lsdir->d_name + aux_string;
            if(file_std_string.substr(file_std_string.find_last_of(".")+1)=="aep"){
                file_paths.push_back(file_std_string);
            }
        }
    }
    closedir(dir);
}

void ChallengeCreator::read_files(){
    for(std::string file : file_paths){
        Challenge* new_challenge = new Challenge(file);
        std::cout << file << std::endl;
        std::string line;
        std::ifstream challenge_file(challenge_paths+"/"+file);
        if(challenge_file.is_open()){
            while(getline(challenge_file, line)){
                if(line == "init"){
                    std::string map;
                    std::string name;
                    std::string obj_x;
                    std::string obj_y;
                    std::string text;
                    std::pair<int, int> position(0,0);
                    getline(challenge_file, name);
                    getline(challenge_file, obj_x);
                    getline(challenge_file, obj_y);
                    getline(challenge_file, text);
                    map = "";
                    do {
                        getline(challenge_file, line);
                        if(line != "end"){
                            map += line;
                        }
                    }
                    while(line != "end");
                    ChallengeMap* new_map = new ChallengeMap(
                        name,
                        position,
                        map,
                        text
                    );
                    new_map->set_obj_initial_position(
                        stoi(obj_x),
                        stoi(obj_y)
                    );
                    new_challenge->add_map(new_map);
                }
            }
        }
        challenges.push_back(new_challenge);
    }
}