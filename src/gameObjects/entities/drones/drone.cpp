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
        coolDown = fireCooldown * (1 - ( (fire_rate_level-1) * fireRateUpgradeBonus));

        GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, 200, position);
        if (!rotates && target) flipSprite = target->getPos().x < position.x;
        fire(position);
    }
    
    
}

void Drone::fire(Vector2 position){}

void Drone::upgradeDamage(){
    damage_level++;
}

void Drone::upgradeFireRate(){
    fire_rate_level++;
}

void Drone::upgradeLevel(){
    level++;
}

bool Drone::canUpgradeDamage(){
    return damage_level < max_damage_level;
}

bool Drone::canUpgradeFireRate(){
    return fire_rate_level < max_fire_rate_level;
}

bool Drone::canUpgradeLevel(){
    return level < maxLevel;
}

bool Drone::getFlipSprite(){
    return flipSprite;
}

float Drone::getScreenSHake(){
    return get_damage() * screenShakeMultiplier;
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
    if (type == type_gun) return false;
    return canUpgradeDamage() || canUpgradeFireRate() || canUpgradeLevel();
}

float Drone::get_damage(){
    return damage * (1 + ((damage_level - 1) * damageUpgradeBonus));
}

int Drone::get_damage_level(){
    return damage_level;
}

int Drone::get_fire_rate_level(){
    return fire_rate_level;
}

int Drone::get_level(){
    return level;
}