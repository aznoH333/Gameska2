#include "Gamestate.h"
#include "raylib.h"
#include "../sprites/SpriteManager.h"

void GameState::init(){}
void GameState::update(){}
void GameState::clear(){}

void UIManager::update(){
    for (int i = 0; i < buttons.size(); i++){
        SpriteManager::getInstance()->drawText(buttons[i].text, button_x_pos, button_y_pos + i * button_offset);

        if (currentlySelectedButton == i){
            SpriteManager::getInstance()->drawTexture(RenderData{"menu_select", {button_x_pos + menu_select_icon_offset, button_y_pos + i * button_offset + menu_select_icon_offset_y}, 4, 0, WHITE, false, layer_priority, true});
            SpriteManager::getInstance()->drawTexture(RenderData{"menu_select", {button_x_pos + menu_select_icon_offset_right, button_y_pos + i * button_offset + menu_select_icon_offset_y}, 4, 0, WHITE, true, layer_priority, true});
            if (IsKeyPressed(KEY_ENTER)) buttons[i].function();
        }
    }

    // move cursor
    if (IsKeyPressed(KEY_W)) {
        currentlySelectedButton--;
        if (currentlySelectedButton < 0)
            currentlySelectedButton = buttons.size() - 1;
    }

    if (IsKeyPressed(KEY_S)){
        currentlySelectedButton++;
        if (currentlySelectedButton >= buttons.size()) 
            currentlySelectedButton = 0;
    }
}

void UIManager::addButton(Button button){
    buttons.push_back(button);
}

void UIManager::clear(){
    buttons.clear();
    currentlySelectedButton = 0;
}

UIManager* UIManager::getInstance(){
    if (!instance) instance = new UIManager();
    return instance;
}

UIManager* UIManager::instance = 0;

void UIManager::dispose(){
    clear();
    delete instance;
}

