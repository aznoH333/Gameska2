#include "GameStateManager.h"
#include "Gamestate.h"

GameStateManager::GameStateManager(){
    // init states
}

GameStateManager* GameStateManager::getInstance(){
    if (!instance) instance = new GameStateManager();
    return instance;
}

void GameStateManager::update(){
    states[currentState]->update();
}


void GameStateManager::switchState(StateName state){
    states[currentState]->clear();
    currentState = state;
    states[currentState]->init();
}

void GameStateManager::dispose(){
    for (std::pair<StateName, GameState*> p : states){
        p.second->clear();
        delete p.second;
    }
    delete instance;
}





GameStateManager* GameStateManager::instance = 0;