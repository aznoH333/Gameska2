#include "gunDrone.h"
#include "drone.h"
#include "../../GameObjectManager.h"
#include "../projectiles/bulletProjectile.h"
#include "raylib.h"

GunDrone::GunDrone() : Drone("Rifle drone", "Amogus_1", 60, 10, 3){}

void GunDrone::fire(Vector2 pos){
    GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::EnemyFlag, 300, pos);
    if (target != nullptr){
        GameObjectManager::getInstance()->addGameObject(new Bullet(pos,
        (std::atan2(target->getPos().x + 32 - (pos.x + 16), -(target->getPos().y  + 32 - (pos.y + 16)))) + (-90 * DEG2RAD),
        damage,
        32.0f
        ));
    }    
}