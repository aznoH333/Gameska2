#include "GameStateManager.h"
#include "Game.h"
#include "MainMenu.h"
#include "MiscStates.h"


GameStateManager::GameStateManager(){
    states[state_main_menu] = new MainMenu();
    states[state_game] = new Game();
    states[state_intro] = new Intro();
    states[state_game_over] = new GameOver();
    states[state_pause] = new Pause_menu();


    states[currentState]->init();
}

GameStateManager* GameStateManager::getInstance(){
    if (!instance) instance = new GameStateManager();
    return instance;
}

void GameStateManager::update(){
    states[currentState]->update();


    // transition related stuff
    if (currentState != nextState){
        transitionValue -= transitionSpeed;
        if (transitionValue <= transitionSpeed){
            transitionValue = 0;
            switchState(nextState);
        }
    }else if (transitionValue <= 1){
        transitionValue += transitionSpeed;
        if (transitionValue > 1) transitionValue = 1;
    }

    SpriteManager::getInstance()->setColorFade(transitionValue);
}


void GameStateManager::switchState(StateName state){
    
    states[currentState]->clear();
    currentState = state;
    if (call_init)
        states[currentState]->init();
}

void GameStateManager::transitionToState(StateName state, bool call_init){
    nextState = state;
    this->call_init = call_init;
}


void GameStateManager::transitionToState(StateName state){
    transitionToState(state, true);
}

void GameStateManager::dispose(){
    for (std::pair<StateName, GameState*> p : states){
        p.second->clear();
        delete p.second;
    }
    delete instance;
}

bool GameStateManager::shouldGameEnd(){
    return exit;
}

void GameStateManager::exitGame(){
    exit = true;
}




GameStateManager* GameStateManager::instance = 0;