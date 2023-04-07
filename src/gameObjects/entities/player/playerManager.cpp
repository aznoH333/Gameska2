#include "playerManager.h"
#include "../../../sprites/SpriteManager.h"
#include "pickups.h"
#include "player.h"
#include "raylib.h"
#include <cmath>

PlayerManager* PlayerManager::getInstance(){
    if (!instance) instance = new PlayerManager();
    return instance;
}


PlayerManager::PlayerManager(){};

void PlayerManager::update(){
    handleUI();
    handle_upgrade_selection();
}



const int gapBetweenHearts = 48;
void PlayerManager::handleUI(){
    SpriteManager* spr = SpriteManager::getInstance();


    if (std::abs(hudPosition.y - desiredHudY) < hudSpeed) hudPosition.y = desiredHudY;
    else hudPosition.y -= std::copysign(hudSpeed, hudPosition.y - desiredHudY);
    // draw hud
    spr->drawTexture({"Hud", hudPosition, 2, 0, WHITE, false, layer_hud, true});

    // draw health
    for (int i = 0; i < maxPlayerHP; i++){
        if (playerObject != nullptr && playerObject->getHealth() > i){
            spr->drawTexture({"Heart", {hudPosition.x - hudWidth + healthOffsetX + (i * gapBetweenHearts), hudPosition.y - healthOffsetY}, 2, 0, WHITE, false, layer_hud, true});
        }else{
            spr->drawTexture({"Empty_Heart", {hudPosition.x - hudWidth + healthOffsetX + (i * gapBetweenHearts), hudPosition.y - healthOffsetY}, 2, 0, WHITE, false, layer_hud, true});

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

void PlayerManager::reset(){
    upgradeCount = 0;
    nextUpgradeCount = 5;
    killCounter = 0;
}

void PlayerManager::confirmKill(Vector2 pos){
    killCounter++;
    
    if (killCounter == nextUpgradeCount){
        killCounter = 0;
        upgradeCount++;
        // next upgrade count calculation
        nextUpgradeCount = upgradeCount * 10 + 5;
        // spawn upgrade
        GameObjectManager::getInstance()->addGameObject(new UpgradePickup(pos));
        
    }
    // TODO spawn hearts
}


void PlayerManager::touchedUpgradeBox(){
    unselected_upgrade_count++;
}


void PlayerManager::handle_upgrade_selection(){
    if (unselected_upgrade_count > 0){
        
        if (IsKeyPressed(KEY_KP_1) || IsKeyPressed(KEY_ONE)){
            playerObject->addDrone(type_gun);
        }else if (IsKeyPressed(KEY_TWO)) {
            playerObject->addDrone(type_shotgun);
        }
        unselected_upgrade_count--;
    }
}

PlayerManager* PlayerManager::instance = 0;