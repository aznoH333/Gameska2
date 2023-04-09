#include "drones.h"
#include "drone.h"
#include "../../GameObjectManager.h"
#include "../projectiles/bulletProjectile.h"
#include "../animationObject/animationObject.h"
#include "raylib.h"

GunDrone::GunDrone() : Drone(type_gun, "Amogus_1", 60, 20, 3, true, 400){}

void GunDrone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);
    if (target != nullptr){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
        GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) + (GetRandomValue(-2, 2) * DEG2RAD),
        damage,
        26.0f
        ));
        

        SpriteManager::getInstance()->addScreenShake(getScreenSHake());

        float rotation = GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos());

        int temp = GetRandomValue(1, 3);
        GameObjectManager::getInstance()->addGameObject(new AnimationObject(
        {pos.x + (std::cos(rotation) * 32 * (flipSprite ? 1 : 1))
        , pos.y + (std::sin(rotation) * 32 * (flipSprite ? 1 : 1))}
        , "Muzzle_flash_", temp, temp+1, 1, false, rotation * RAD2DEG));
        
    }    
}

ShotGunDrone::ShotGunDrone() : Drone(type_shotgun, "Amogus_4", 90, 10, 3, true, 250){}

void ShotGunDrone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);
    if (target != nullptr){
        for (int i = 0; i < 3 + level; i++){
            GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) + (GetRandomValue(-5, 5) * DEG2RAD),
            damage,
            26.0f
            ));

            SpriteManager::getInstance()->addScreenShake(getScreenSHake());
        }

        float rotation = GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos());

        int temp = GetRandomValue(1, 3);
        GameObjectManager::getInstance()->addGameObject(new AnimationObject(
        {pos.x + (std::cos(rotation) * 32 * (flipSprite ? 1 : 1))
        , pos.y + (std::sin(rotation) * 32 * (flipSprite ? 1 : 1))}
        , "Muzzle_flash_", temp, temp+1, 1, false, rotation * RAD2DEG));
        
    }
}