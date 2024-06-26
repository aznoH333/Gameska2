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

        Sound_manager::get_instance()->play_sound("gun");

        

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
            Sound_manager::get_instance()->play_sound("shotgun");

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
        
        
        Sound_manager::get_instance()->play_sound("gun", 0.5f);


        SpriteManager::getInstance()->addScreenShake(std::min(getScreenSHake(), 10.0f));
        
        for (int i = 0; i < level; i++){
            GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) + (GetRandomValue(-7, 7) * DEG2RAD),
            get_damage(),
            28.0f,
            projectile_bullet
            ));
            


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

Laser_drone::Laser_drone(): Drone(type_laser, "Amogus_2", 75, 20, 2, false, 500){}

void Laser_drone::fire(Vector2 pos){
    float adder = 45.0f / level;
    Sound_manager::get_instance()->play_sound("laser", 0.7f);
    
    for (float i = 0; i < 359; i += adder){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            i * DEG2RAD,
            get_damage(),
            32.0f,
            projectile_laser
            ));
    }
}


// rocket drone

Rocket_drone::Rocket_drone(): Drone(type_rocket, "Amogus_5", 240, 30, 3, false, 700){}

void Rocket_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);

    if (target != nullptr){
        Sound_manager::get_instance()->play_sound("rocket");
        
        GameObjectManager::getInstance()->addGameObject(new Rocket(pos, get_damage() + ((level - 1) * 10), 10 + ((level - 1) * 5), 270));
    }
}


// sniper drone

Sniper_drone::Sniper_drone(): Drone(type_sniper, "Amogus_3", 120, 10, 3, false, 700){

}

void Sniper_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);
    Sound_manager::get_instance()->play_sound("laser");

    if (target != nullptr){
        
        float rotation = GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos());
        
        for (int i = 10 + (level * 5); i > 0; i -= 5){
            GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
            rotation,
            get_damage(),
            20.0f + i,
            projectile_laser
        ));
        }
        
    }
}

Destroyer_drone::Destroyer_drone (): Drone(type_sniper, "Amogus_7", 240, 30, 2, false, 700){

}

void Destroyer_drone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, range, pos);

    if (target != nullptr){
        Sound_manager::get_instance()->play_sound("rocket");
        

        for(int i = 0; i < level * 3; i++){
        GameObjectManager::getInstance()->addGameObject(new Rocket(pos, get_damage() + ((level - 1) * 10), 10 + ((level - 1) * 5), GetRandomValue(0, 360)));

        }
    }
}