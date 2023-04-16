#include "MiscStates.h"
#include "Game.h"
#include "GameStateManager.h"
#include "Gamestate.h"
#include "raylib.h"
#include <string>

void Intro::update(){
    introTimer--;
    
    if (introTimer <= 0 || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) 
        GameStateManager::getInstance()->transitionToState(state_main_menu);

    // draw logo
    SpriteManager::getInstance()->drawTexture(RenderData{"Among", {logoX, logoY}, 4, 0, WHITE, false, layer_priority});
}


void Intro::clear(){
    
}

void Game_Over::init(){
    UIManager::getInstance()->addButton({"Retry", [](){GameStateManager::getInstance()->transitionToState(state_game);}});
    UIManager::getInstance()->addButton({"Menu", [](){GameStateManager::getInstance()->transitionToState(state_main_menu);}});
    survived_time += std::to_string(World::getInstance()->get_time_minutes()) + " : ";
    int temporary = World::getInstance()->get_time_seconds();
    if (temporary < 10) survived_time += "0";
    survived_time += std::to_string(temporary);

}

void Game_Over::update(){
    SpriteManager::getInstance()->drawText("GAME OVER", game_over.x, game_over.y, 1.3f, true);
    SpriteManager::getInstance()->drawText("You survived for :", survived_text.x, survived_text.y, 0.7f, true);
    SpriteManager::getInstance()->drawText(survived_time, survived_timer.x, survived_timer.y, 0.7f, true);




    

    UIManager::getInstance()->update();
}

void Game_Over::clear(){
    UIManager::getInstance()->clear();
    survived_time = "";
}

void Pause_Menu::init(){
    UIManager::getInstance()->addButton({"Continue", [](){GameStateManager::getInstance()->transitionToState(state_game, false);}});
    UIManager::getInstance()->addButton({"Exit", [](){GameStateManager::getInstance()->transitionToState(state_main_menu);}});
}

void Pause_Menu::update(){
    UIManager::getInstance()->update();
}

void Pause_Menu::clear(){
    UIManager::getInstance()->clear();
}


// options menu
void Options_Menu::init(){
    // screen shake
    UIManager::getInstance()->addButton({"Shake", 
    [](){Persistent_Data_Manager::get_instance()->get_data()->screen_shake = !Persistent_Data_Manager::get_instance()->get_data()->screen_shake;}, 
    true, Persistent_Data_Manager::get_instance()->get_data()->screen_shake});

    UIManager::getInstance()->addButton({"Gore", 
    [](){Persistent_Data_Manager::get_instance()->get_data()->gore = !Persistent_Data_Manager::get_instance()->get_data()->gore;}, 
    true, Persistent_Data_Manager::get_instance()->get_data()->gore});
    
    UIManager::getInstance()->addButton({"Menu", [](){GameStateManager::getInstance()->transitionToState(state_main_menu);}});
}

void Options_Menu::update(){
    // backdrop
    backdrop_offset += backdrop_speed;

    //CameraObject::getInstance()->update();

    if (backdrop_offset > 128) backdrop_offset -= 128;
    
    
    for (float x = 0; x <= 1280; x += 128){
        for (float y = 0; y < 720; y += 128){
            SpriteManager::getInstance()->drawTexture({"menu_backdrop", {x - backdrop_offset + 128, y + 128}, 2, 0, WHITE, false, layer_world, true});
        }
    }

    // exit window
    if (IsKeyPressed(KEY_ESCAPE)){
        GameStateManager::getInstance()->transitionToState(state_main_menu);
    }

    // update
    UIManager::getInstance()->update();
}

void Options_Menu::clear(){
    UIManager::getInstance()->clear();
}