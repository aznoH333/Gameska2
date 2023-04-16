#include "MainMenu.h"
#include "GameStateManager.h"
#include "raylib.h"


MainMenu::MainMenu(){}

void MainMenu::init(){
    
    UIManager::getInstance()->addButton({"Play", [](){GameStateManager::getInstance()->transitionToState(state_game);}});
    UIManager::getInstance()->addButton({"Options", [](){GameStateManager::getInstance()->transitionToState(state_options);}});    
    UIManager::getInstance()->addButton({"Exit", [](){GameStateManager::getInstance()->exitGame();}});

}

void MainMenu::update(){
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
        GameStateManager::getInstance()->exitGame();
    }

    // update
    UIManager::getInstance()->update();
}

void MainMenu::clear(){
    UIManager::getInstance()->clear();
}