#include "drones.h"
#include "drone.h"
#include "../../GameObjectManager.h"
#include "../projectiles/bulletProjectile.h"
#include "../animationObject/animationObject.h"
#include "raylib.h"

GunDrone::GunDrone() : Drone("Rifle drone", "Amogus_1", 60, 20, 3){}

void GunDrone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, 300, pos);
    if (target != nullptr){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
        (std::atan2(target->getPos().x + 32 - (pos.x + 16), -(target->getPos().y  + 32 - (pos.y + 16)))) + (-90 * DEG2RAD),
        damage,
        26.0f
        ));

        SpriteManager::getInstance()->addScreenShake(getScreenSHake());


        int temp = GetRandomValue(1, 3);
        GameObjectManager::getInstance()->addGameObject(new AnimationObject(
        {pos.x + (flipSprite ? -16 : 32), pos.y + 8}
        , "Muzzle_flash_", temp, temp+1, 1, flipSprite));
        
    }    
}

ShotGunDrone::ShotGunDrone() : Drone("Shotgun drone", "Amogus_4", 90, 10, 3){}

void ShotGunDrone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, 200, pos);
    if (target != nullptr){
        for (int i = 0; i < 3 + level; i++){
            GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            (std::atan2(target->getPos().x + 32 - (pos.x + 16), -(target->getPos().y  + 32 - (pos.y + 16)))) + ((-90 + GetRandomValue(-5, 5)) * DEG2RAD),
            damage,
            26.0f
            ));
        }
        
        SpriteManager::getInstance()->addScreenShake(getScreenSHake());

        int temp = GetRandomValue(1, 3);
        GameObjectManager::getInstance()->addGameObject(new AnimationObject(
        {pos.x + (flipSprite ? -16 : 32), pos.y + 8}
        , "Muzzle_flash_", temp, temp+1, 1, flipSprite));
        
    }
}