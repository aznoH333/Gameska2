#include "MainMenu.h"
#include "Gamestate.h"

void MainMenu::init(){
    buttons.push_back(Button{"Play", [](){}});
    buttons.push_back(Button{"Exit", [](){}});
}

void MainMenu::update(){
    for (int i = 0; i < buttons.size(); i++){
        DrawText(buttons[i].text.c_str(), 200, 400 + i * 64, 4, WHITE);
    }
}

void MainMenu::clear(){
    buttons.clear();
}