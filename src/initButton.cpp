#include "../inc/initButton.hpp"

InitButton::InitButton(
    std::string object_name,
    std::pair<int,int>object_position,
    std::pair<int,int>object_size
){
    set_name(object_name);
    set_position(object_position);
    set_size(object_size);
}

void InitButton::set_selector(Selector* p_selector){
    selector = p_selector;
}

void InitButton::set_challenge_creator(ChallengeCreator* p_creator){
    challenge_creator = p_creator;
}

void InitButton::execute(){
    if(is_active){
        Engine::Collider& collider = Engine::Collider::get_instance();
        collider.remove_all_objects();
        if(selector){
            robot_sprite = selector->get_selected_sprite();
        }
        if(challenge_creator){
            Engine::Game& game = Engine::Game::get_instance();
            if(game.search_screen(challenge_name)){
                game.load_screen(challenge_name);
            } else {
                Challenge* current_challenge = (
                    challenge_creator->get_challenge_by_title(challenge_name)
                );
                for(int i = 0; i < user_progress; i++){
                    current_challenge->set_map_complete(i);
                }
                new_challenge = new ChallengeScreen(
                    challenge_name,
                    challenge_creator->get_challenge_by_title(challenge_name)
                );
                new_challenge->set_player_sprite(robot_sprite);
                game.add_screen(new_challenge);
                game.load_screen(challenge_name);
            }
            deactivate();
        }
    }
}

void InitButton::set_challenge_info(std::string title, int progress){
    challenge_name = title;
    user_progress = progress;
}