#include "pickups.h"
#include "playerManager.h"
#include "raylib.h"



UpgradePickup::UpgradePickup(Vector2 pos) : GameObject(pos, {64,64}, ObjectIdentifier::Other, 1){}

void UpgradePickup::update(){
    
    SpriteManager::getInstance()->drawTexture({"Upgrade_box", {pos.x, pos.y - z}, 2 * scaleModifier, 0, WHITE, false, layer_pickups + zIndex});
    // get sign
    if (!isAirborne && timer % 20 > 5){
        SpriteManager::getInstance()->drawTexture({"Grab_text", {pos.x - 6, pos.y - sign_offset}, 2, 0, WHITE, false, layer_priority});
    }


    // gravity stuff
    if (isAirborne){
        zVelocity -= zGravity;
        
        if (z + zVelocity < 0){
            z = 0;
            isAirborne = false;
            zIndex = 0;
        }else {
            z += zVelocity;
        }   
    }

    if (scaleModifier < 1){
        scaleModifier += scaleModifierIncreaseSpeed;

        if (scaleModifier >= 1){
            scaleModifier = 1;
        }
    }

    timer++;
}


void UpgradePickup::onCollide(GameObject *other){
    if (other->getObjectIdentifier() == ObjectIdentifier::PlayerFlag){
        destroy();
        PlayerManager::getInstance()->touchedUpgradeBox();
    }
}