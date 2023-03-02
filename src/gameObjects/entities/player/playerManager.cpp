#include "playerManager.h"
#include "../../../sprites/SpriteManager.h"
#include "raylib.h"
#include <cmath>

PlayerManager* PlayerManager::getInstance(){
    if (!instance) instance = new PlayerManager();
    return instance;
}


PlayerManager::PlayerManager(){};

void PlayerManager::update(){
    handleUI();
}



const int gapBetweenHearts = 48;
void PlayerManager::handleUI(){
    SpriteManager* spr = SpriteManager::getInstance();


    if (std::abs(hudPosition.y - desiredHudY) < hudSpeed) hudPosition.y = desiredHudY;
    else hudPosition.y -= std::copysign(hudSpeed, hudPosition.y - desiredHudY);
    // draw hud
    spr->drawTextureAbsolute("Hud", hudPosition, 2, 0, WHITE, false);

    // draw health
    for (int i = 0; i < maxPlayerHP; i++){
        if (playerObject != nullptr && playerObject->getHealth() > i){
            spr->drawTextureAbsolute("Heart", {hudPosition.x - hudWidth + healthOffsetX + (i * gapBetweenHearts), hudPosition.y - healthOffsetY}, 2, 0, WHITE, false);
        }else{
            spr->drawTextureAbsolute("Empty_Heart", {hudPosition.x - hudWidth + healthOffsetX + (i * gapBetweenHearts), hudPosition.y - healthOffsetY}, 2, 0, WHITE, false);

        }
    }

}


void PlayerManager::registerPlayerObject(Player *player){
    playerObject = player;
}

void PlayerManager::removePlayer(){
    playerObject = nullptr;
}



void PlayerManager::dispose(){
    delete instance;
}

PlayerManager* PlayerManager::instance = 0;