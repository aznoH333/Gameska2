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

void GameOver::init(){
    UIManager::getInstance()->addButton({"Retry", [](){GameStateManager::getInstance()->transitionToState(state_game);}});
    UIManager::getInstance()->addButton({"Menu", [](){GameStateManager::getInstance()->transitionToState(state_main_menu);}});
    survived_time += std::to_string(World::getInstance()->get_time_minutes()) + " : ";
    int temporary = World::getInstance()->get_time_seconds();
    if (temporary < 10) survived_time += "0";
    survived_time += std::to_string(temporary);

}

void GameOver::update(){
    SpriteManager::getInstance()->drawText("GAME OVER", game_over.x, game_over.y, 1.3f, true);
    SpriteManager::getInstance()->drawText("You survived for :", survived_text.x, survived_text.y, 0.7f, true);
    SpriteManager::getInstance()->drawText(survived_time, survived_timer.x, survived_timer.y, 0.7f, true);




    

    UIManager::getInstance()->update();
}

void GameOver::clear(){
    UIManager::getInstance()->clear();
    survived_time = "";
}

void Pause_menu::init(){
    UIManager::getInstance()->addButton({"Continue", [](){GameStateManager::getInstance()->transitionToState(state_game, false);}});
    UIManager::getInstance()->addButton({"Exit", [](){GameStateManager::getInstance()->transitionToState(state_main_menu);}});
}

void Pause_menu::update(){
    UIManager::getInstance()->update();
}

void Pause_menu::clear(){
    UIManager::getInstance()->clear();
}