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
    spr->drawTexture({"Hud", hudPosition, 2, 0, WHITE, false, 3, true});

    // draw health
    for (int i = 0; i < maxPlayerHP; i++){
        if (playerObject != nullptr && playerObject->getHealth() > i){
            spr->drawTexture({"Heart", {hudPosition.x - hudWidth + healthOffsetX + (i * gapBetweenHearts), hudPosition.y - healthOffsetY}, 2, 0, WHITE, false, 3, true});
        }else{
            spr->drawTexture({"Empty_Heart", {hudPosition.x - hudWidth + healthOffsetX + (i * gapBetweenHearts), hudPosition.y - healthOffsetY}, 2, 0, WHITE, false, 3, true});

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