#include "playerManager.h"
#include "../../../sprites/SpriteManager.h"
#include "pickups.h"
#include "player.h"
#include "raylib.h"
#include <cmath>
#include <string>
#include <vector>

PlayerManager* PlayerManager::getInstance(){
    if (!instance) instance = new PlayerManager();
    return instance;
}


PlayerManager::PlayerManager(){
};

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
    drone_count = 1;
    //unselected_upgrade_count = 0;
    generate_upgrades();
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


void PlayerManager::handle_upgrade_action(KeyboardKey key, int upgrade_slot){
    Drone_upgrade upgrade = upgrades[upgrade_slot];
    
    if (IsKeyPressed(key) && upgradeCount > 0){


        switch (upgrade.action) {
            
            default:
            case action_add_drone:
                playerObject->addDrone(upgrade.type);
                drone_count++;
                break;

            case action_replace:
                (*playerObject->get_drones()).erase((*playerObject->get_drones()).begin() + upgrade.action_index);
                playerObject->addDrone(upgrade.type);
                break;

            case action_upgrade_damage:
                (*playerObject->get_drones())[upgrade.action_index]->upgradeDamage(); // could be better but this is good enough
                break;

            case action_upgrade_fire_rate:
                (*playerObject->get_drones())[upgrade.action_index]->upgradeFireRate();
                break;

            case action_upgrade_level:
                (*playerObject->get_drones())[upgrade.action_index]->upgradeLevel();
                break;
        }

        unselected_upgrade_count--;
        generate_upgrades();
    }
    
    
}


void PlayerManager::touchedUpgradeBox(){
    unselected_upgrade_count++;
    generate_upgrades();

}


void PlayerManager::handle_upgrade_selection(){
    if (unselected_upgrade_count > 0){
        SpriteManager::getInstance()->drawText("Among " + std::to_string(unselected_upgrade_count), 20, 20);

        handle_upgrade_action(KEY_KP_1, 0);
        handle_upgrade_action(KEY_KP_2, 1);
        handle_upgrade_action(KEY_KP_3, 2);

    }
}


void PlayerManager::generate_upgrades(){
    upgrades.clear();
    std::vector<Drone*> drones = *playerObject->get_drones();
    
    for (int i = 0; i < 3; i++){
        
        Drone* current_drone = drones[i];
        
        if (i >= drone_count){
            // add drone action
            upgrades.push_back({action_add_drone, i, type_gun}); // TODO randomize type selection
        
        }else if (current_drone != nullptr && GetRandomValue(0, 2) >= 1 && current_drone->can_be_upgraded()){
            
            // upgrade drone
            upgrades.push_back({choose_random_upgrade(current_drone), i, type_gun});
        
        } else {
            
            // replace drone
            upgrades.push_back({action_replace, i, type_gun}); // TODO randomize type selection
            

        }
    }
    
}



Upgrade_action PlayerManager::choose_random_upgrade(Drone* drone){
    std::vector<Upgrade_action> temp;

    if (drone->canUpgradeDamage())      temp.push_back(action_upgrade_damage);
    if (drone->canUpgradeFireRate())    temp.push_back(action_upgrade_fire_rate);
    if (drone->canUpgradeLevel())       temp.push_back(action_upgrade_level);

    return temp[GetRandomValue(0, temp.size()-1)];
}



PlayerManager* PlayerManager::instance = 0;