#include "MiscStates.h"
#include "Game.h"
#include "GameStateManager.h"
#include "Gamestate.h"
#include "raylib.h"

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

}

void GameOver::update(){
    UIManager::getInstance()->update();
}

void GameOver::clear(){
    UIManager::getInstance()->clear();
}