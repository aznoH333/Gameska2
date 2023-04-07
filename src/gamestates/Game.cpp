#include "Game.h"
#include "GameStateManager.h"

void Game::init(){
    GameObjectManager::getInstance()->addGameObject(new Player({0,200}));
    PlayerManager::getInstance()->reset();
}

void Game::update(){
    World::getInstance()->update();
    SpriteManager::getInstance()->update();
    GameObjectManager::getInstance()->update();
    CameraObject::getInstance()->update();
    PlayerManager::getInstance()->update();

    if (IsKeyPressed(KEY_ESCAPE)){
        GameStateManager::getInstance()->transitionToState(state_main_menu);
    }
}

void Game::clear(){
    GameObjectManager::getInstance()->clear();
    PlayerManager::getInstance()->removePlayer();
    CameraObject::getInstance()->setCameraPos({0,0});
}