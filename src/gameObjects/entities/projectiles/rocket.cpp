#include "rocket.h"
#include "raylib.h"
#include "../animationObject/animationObject.h"

Rocket::Rocket(Vector2 pos, float damage, float speed, float startingRotation) : GameObject(pos, {16,16}, ObjectIdentifier::PlayerProjectileFlag, 1){
    this->damage = damage;
    this->speed = speed;
    this->rotation = startingRotation;
}

void Rocket::update(){
    
    if (is_exploding){
        explosion();
        explosion_timer--;
        if (explosion_timer <= 0) destroy();
    }else{
        seek_target();
        life_time--;

        if (life_time <= 0) explode();
    }

}


void Rocket::seek_target(){
    
    SpriteManager::getInstance()->drawTexture({"rocket", pos, 2, rotation, WHITE, false, layer_projectiles});
    if (life_time % 2 == 0) GameObjectManager::getInstance()->addGameObject(new AnimationObject(pos, "smoke_", 1, 3, 4, false, GetRandomValue(0, 360)));
    
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
            explode();
        }else {
            other->takeDamage(damage, this, GetRandomValue(0, 360) * DEG2RAD);
        }
    }
}

void Rocket::explode(){
    Sound_manager::get_instance()->play_sound("explosion");
    SpriteManager::getInstance()->addScreenShake(25);
    is_exploding = true;
    GameObjectManager::getInstance()->addGameObject(new AnimationObject({pos.x - 64, pos.y - 64}, "explosion_", 1, 9, 2, false, GetRandomValue(0, 360)));
    size = {128,128};
    pos.x -= 64;
    pos.y -= 64;
}

void Rocket::onDestroy(){

}