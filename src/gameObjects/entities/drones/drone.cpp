#include "drone.h"
#include <string>
#include "../../GameObjectManager.h"

Drone::Drone(std::string name, std::string sprite, int fireCooldown, float damage, int maxLevel){
    this->name = name;
    this->sprite = sprite;
    this->fireCooldown = fireCooldown;
    this->damage = damage;
    this->maxLevel = maxLevel;
}

std::string Drone::getName(){
    return name;
}

std::string Drone::getSprite(){
    return sprite;
}

void Drone::update(Vector2 position){
    if (coolDown > 0) coolDown--;
    else{
        coolDown = fireCooldown * fireRateUpgrade;
        fire(position);

        GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, 200, position);
        if (target) flipSprite = target->getPos().x < position.x;
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