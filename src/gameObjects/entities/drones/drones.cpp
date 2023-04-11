#include "drones.h"
#include "drone.h"
#include "../../GameObjectManager.h"
#include "../projectiles/bulletProjectile.h"
#include "../projectiles/rocket.h"
#include "../animationObject/animationObject.h"
#include "raylib.h"

Gun_drone::Gun_drone() : Drone(type_gun, "Amogus_1", 60, 15, 1, true, 450){}

void Gun_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);
    if (target != nullptr){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
        GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) + (GetRandomValue(-2, 2) * DEG2RAD),
        get_damage(),
        26.0f,
        projectile_bullet
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

// shotgun
Shotgun_drone::Shotgun_drone() : Drone(type_shotgun, "Amogus_4", 90, 10, 3, true, 350){}

void Shotgun_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);
    if (target != nullptr){
        for (int i = 0; i < 3 + level; i++){
            GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) + (GetRandomValue(-5, 5) * DEG2RAD),
            get_damage(),
            26.0f,
            projectile_bullet
            ));

        }

        SpriteManager::getInstance()->addScreenShake(getScreenSHake());


        float rotation = GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos());

        int temp = GetRandomValue(1, 3);
        GameObjectManager::getInstance()->addGameObject(new AnimationObject(
        {pos.x + (std::cos(rotation) * 32 * (flipSprite ? 1 : 1))
        , pos.y + (std::sin(rotation) * 32 * (flipSprite ? 1 : 1))}
        , "Muzzle_flash_", temp, temp+1, 1, false, rotation * RAD2DEG));
        
    }
}

// machine gun
Machinegun_drone::Machinegun_drone(): Drone(type_machinegun, "Amogus_6", 15, 7, 2, true, 400){}

void Machinegun_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);
    if (target != nullptr){
        
        for (int i = 0; i < level; i++){
            GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) + (GetRandomValue(-7, 7) * DEG2RAD),
            get_damage(),
            28.0f,
            projectile_bullet
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
}

// laser drone 

Laser_drone::Laser_drone(): Drone(type_laser, "Amogus_2", 60, 20, 2, false, 500){}

void Laser_drone::fire(Vector2 pos){
    int adder = 45 / level;
    for (int i = 0; i < 360; i += adder){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            i * DEG2RAD,
            get_damage(),
            32.0f,
            projectile_laser
            ));
    }
}


// rocket drone

Rocket_drone::Rocket_drone(): Drone(type_rocket, "Amogus_5", 120, 30, 3, false, 700){}

void Rocket_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);

    if (target != nullptr){
        GameObjectManager::getInstance()->addGameObject(new Rocket(pos, get_damage() * (level), 10 * (level)));
    }
}


// sniper drone

Sniper_drone::Sniper_drone(): Drone(type_sniper, "Amogus_3", 120, 45, 3, false, 700){

}

void Sniper_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);

    if (target != nullptr){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
        GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()),
        get_damage() * level,
        35.0f * level,
        projectile_laser
        ));
    }
}