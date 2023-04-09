#include "drone.h"
#include <string>
#include "../../GameObjectManager.h"

Drone::Drone(Drone_type type, std::string sprite, float fireCooldown, float damage, int maxLevel, bool rotates, float range){
    this->type = type;
    this->sprite = sprite;
    this->fireCooldown = fireCooldown;
    this->damage = damage;
    this->maxLevel = maxLevel;
    this->rotates = rotates;
    this->range = range;
}

Drone_type Drone::get_type(){
    return type;
}

std::string Drone::getSprite(){
    return sprite;
}

void Drone::update(Vector2 position){
    if (coolDown > 0) coolDown--;
    else{
        coolDown = fireCooldown * fireRateUpgrade;

        GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, 200, position);
        if (!rotates && target) flipSprite = target->getPos().x < position.x;
        fire(position);
    }
    
    
}

void Drone::fire(Vector2 position){}

void Drone::upgradeDamage(){
    damageUpgrade += damageUpgradeBonus;
}

void Drone::upgradeFireRate(){
    fireRateUpgrade -= fireRateUpgradeBonus;
}

void Drone::upgradeLevel(){
    level++;
}

bool Drone::canUpgradeDamage(){
    return damageUpgrade < maxDamageBonus;
}

bool Drone::canUpgradeFireRate(){
    return fireRateUpgrade > maxFireRateBonus;
}

bool Drone::canUpgradeLevel(){
    return level < maxLevel;
}

bool Drone::getFlipSprite(){
    return flipSprite;
}

float Drone::getScreenSHake(){
    return damage * screenShakeMultiplier;
}

bool Drone::doesRotate(){
    return rotates;
}

float Drone::getRange(){
    return range;
}

void Drone::setFlipSprite(bool flip){
    flipSprite = flip;
}

bool Drone::can_be_upgraded(){
    return canUpgradeDamage() || canUpgradeFireRate() || canUpgradeLevel();
}