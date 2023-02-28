#include "bulletProjectile.h"
#include "raylib.h"
#include "../../../sprites/SpriteManager.h"


Bullet::Bullet(Vector2 pos, float rotation, float damage, float speed) : GameObject(pos, {16,16}, ObjectIdentifier::PlayerProjectileFlag, 1){
    this->rotation = rotation;
    this->damage = damage;
    this->speed = speed;
}

void Bullet::update(){
    pos.x += std::cos(rotation) * speed;
    pos.y += std::sin(rotation) * speed;

    SpriteManager::getInstance()->drawTexture("missing", pos, 2, WHITE, false);
}

void Bullet::onCollide(GameObject* other){
    if (other->getObjectIdentifier() == ObjectIdentifier::EnemyFlag){
        other->takeDamage(damage, this, rotation);
        destroy();
    }
}

void Bullet::onDestroy(){

}