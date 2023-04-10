#include "rocket.h"
#include "raylib.h"


Rocket::Rocket(Vector2 pos, float damage, float speed) : GameObject(pos, {16,16}, ObjectIdentifier::PlayerProjectileFlag, 1){
    this->damage = damage;
    this->speed = speed;
}

void Rocket::update(){
    
    if (is_exploding){
        explosion();
    }else{
        seek_target();
        life_time--;

        if (life_time <= 0) is_exploding = true;
    }

}


void Rocket::seek_target(){
    
    SpriteManager::getInstance()->drawTexture({"rocket", pos, 2, rotation, WHITE, false, layer_projectiles});
    
    
    if (targeting_time > 0){
        // short targeting period
        targeting_time--;

        pos.y -= speed * acceleration_multiplier;
    }else {
        // chase target
        GameObject* target = GameObjectManager::getInstance()->findClosestEntityWithTag(EnemyFlag, 700, pos);

        if (target != nullptr){
            if (acceleration_multiplier < 1) acceleration_multiplier += acceleration;

            float rotation_towards_target = GameObjectManager::getInstance()->getRotationTowarsObject(pos, target->getPos()) * RAD2DEG;

            if (rotation_towards_target < 0) rotation_towards_target += 360;
            if (rotation < 0) rotation += 360;
            if (rotation > 360) rotation -= 360;

            if (rotation - rotation_towards_target > 0 && rotation - rotation_towards_target < 180) 
                rotation -= rotation_speed * acceleration_multiplier;
            else 
                rotation += rotation_speed * acceleration_multiplier;

            

            
        }

        pos.x += std::cos(rotation * DEG2RAD) * speed * acceleration_multiplier;
        pos.y += std::sin(rotation * DEG2RAD) * speed * acceleration_multiplier;
    }
}

void Rocket::explosion(){

}


void Rocket::onCollide(GameObject *other){
    
    if (other->getObjectIdentifier() == EnemyFlag){
        // explode
        if (!is_exploding){
            is_exploding = true;
        }else {
            // deal damage
        }
    }
}

void Rocket::onDestroy(){

}