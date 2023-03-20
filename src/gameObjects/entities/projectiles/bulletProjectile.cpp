#include "bulletProjectile.h"
#include "raylib.h"
#include "../../../sprites/SpriteManager.h"
#include "../../world/world.h"


Bullet::Bullet(Vector2 pos, float rotation, float damage, float speed) : GameObject(pos, {16,16}, ObjectIdentifier::PlayerProjectileFlag, 1){
    this->rotation = rotation;
    this->damage = damage;
    this->speed = speed;
}

void Bullet::update(){
    pos.x += std::cos(rotation) * speed;
    pos.y += std::sin(rotation) * speed;

    SpriteManager::getInstance()->drawTexture({"bullet", pos, 2, rotation * RAD2DEG, WHITE, false, 2});


    // projectiles wont be deleted by walls for the first 30 frames
    if (spawnTimer > 0)spawnTimer--;

    // wall collisions
    if (spawnTimer == 0 && (pos.x + size.x > WORLD::worldWidth || pos.x < -WORLD::worldWidth + 64.0f || pos.y < -WORLD::worldHeight - size.y + 64 || pos.y > WORLD::worldHeight))
        destroy();
    
}

void Bullet::onCollide(GameObject* other){
    if (other->getObjectIdentifier() == ObjectIdentifier::EnemyFlag){
        other->takeDamage(damage, this, rotation);
        destroy();
    }
}

void Bullet::onDestroy(){

}