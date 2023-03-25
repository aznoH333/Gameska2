#include "MainMenu.h"
#include "GameStateManager.h"


MainMenu::MainMenu(){}

void MainMenu::init(){
    UIManager::getInstance()->addButton({"Play", [](){GameStateManager::getInstance()->transitionToState(state_game);}});
    UIManager::getInstance()->addButton({"Exit", [](){GameStateManager::getInstance()->exitGame();}});

}

void MainMenu::update(){
    UIManager::getInstance()->update();
}

void MainMenu::clear(){
    UIManager::getInstance()->clear();
}