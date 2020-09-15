#include <iostream>

#include "../inc/game.hpp"

using namespace Engine;

Game* Game::instance = NULL;

Game& Game::get_instance(){
    if(!instance){
        Log().print("Primeiramente inicialize uma instancia");
    } else {
        return *instance;
    }
}

Game& Game::initialize(
    std::string game_name,
    std::pair<int, int> window_dimensions
){  
    if(!instance){
        instance = new Game();
        instance->set_information(game_name, window_dimensions);
        instance->init();
    }
    return *instance;
}

void Game::set_information(
    std::string game_name,
    std::pair<int, int> window_dimensions
){
    set_name(game_name);
    set_window_dimensions(window_dimensions);
}

bool Game::init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
        Log().print("Houve um problema ao inicializar a SDL");
        success = false;
    }
    window = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_dimensions.first,
        instance->window_dimensions.second,
        SDL_WINDOW_SHOWN
    );
    if(!window){
        Log().print("Houve um problema ao inicializar a janela");
        success = false;
    } else {
        renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == NULL){
            Log().print("Nao foi possivel criar o renderer!");
            success = false;
        }
    }
    int imageFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imageFlags) & imageFlags)){
        Log().print("Houve um problema ao inicializar o modulo de imagem da SDL2");
        success = false;
    }
    if(TTF_Init() == -1){
        Log().print("Houve um problema ao inicializar o modulo de textos da SDL2");
        success = false;     
    }
    return success;
}

void Game::close(){
    SDL_DestroyTexture(current_texture);
    current_texture = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

void Game::run(){
    SDL_Event e;
    bool quit = false;
    bool renderText = false;
    SDL_StartTextInput();

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }
//PARTE TESTE TEXT INPUT--------------------------------------------------------------
            // //Special key input
            // else if( e.type == SDL_KEYDOWN )
            // {
            //     //Handle backspace
            //     // if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
            //     if( e.key.keysym.sym == SDLK_BACKSPACE)
            //     {
            //         //lop off character
            //         // inputText.pop_back();
            //         renderText = true;
            //     }
            //     //Handle copy
            //     else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
            //     {
            //         // SDL_SetClipboardText( inputText.c_str() );
            //     }
            //     //Handle paste
            //     else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
            //     {
            //         // inputText = SDL_GetClipboardText();
            //         renderText = true;
            //     }
            // }
            // //Special text input event
            // else if( e.type == SDL_TEXTINPUT )
            // {
            //     //Not copy or pasting
            //     if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
            //     {
            //         //Append character
            //         // inputText += e.text.text;
            //         renderText = true;
            //     }
            // }
        }

        // //Rerender text if needed
        // if( renderText )
        // {
        //     //Text is not empty
        //     if( inputText != "" )
        //     {
        //         //Render new text
        //         SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, inputText.c_str(), textColor );
        //         current_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        //     }
        //     //Text is empty
        //     else
        //     {
        //         //Render space texture
        //         std::string x = " ";
        //         SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, x.c_str(), textColor );
        //         current_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        //     }
        // }

        // //Clear screen
        // // SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        // SDL_RenderClear( renderer );
        // SDL_Rect renderQuad = {0,0 , 250, 800};
        
        // SDL_RenderCopy(renderer, current_texture, NULL, &renderQuad);
        // SDL_RenderPresent( renderer );
//------------------------------------------------------------------------------------
        SDL_SetRenderDrawColor(renderer, 0xD3, 0xD3, 0xD3, 0x00);
        SDL_RenderClear(renderer);
        draw_objects();
        SDL_RenderPresent(renderer);
    }
    close();
}

void Game::set_name(std::string game_name){
    name = game_name;
}

std::string Game::get_name(){
    return name;
}

SDL_Renderer *Game::get_renderer(){
    return renderer;
}

void Game::set_window_dimensions(std::pair<int, int> dimensions){
  window_dimensions = dimensions;
}

std::pair<int, int> Game::get_window_dimensions(){
  return window_dimensions;
}

void Game::add_object(GameObject* object){
    objects.push_back(object);
}

void Game::add_textfield(TextField* object){
    text_fields.push_back(object);
}

void Game::load_objects(){
    for(auto object : objects){
        object->load();
    }
    for(auto field : text_fields){
        field->load();
    }
}

void Game::draw_objects(){
    for(auto object : objects){
        object->draw();
    }
    for(auto field : text_fields){
        field->draw();
    }
}