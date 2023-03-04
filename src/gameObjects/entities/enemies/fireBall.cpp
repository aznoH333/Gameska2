#include "fireBall.h"
#include "enemy.h"
#include "fireEnemy.h"
#include <cmath>
#include "../../world/world.h"
#include "../animationObject/animationObject.h"

Fireball::Fireball(Vector2 pos, float direction, bool flipSprite, float rotation) : GameObject(pos, {24,24}, ObjectIdentifier::EnemyProjectileFlag,1){
    this->direction = direction;
    this->flipSprite = flipSprite;
    this->rotation = rotation;
}


void Fireball::update(){
    // move
    pos.x += std::cos(direction) * speed;
    pos.y += std::sin(direction) * speed;
    rotation++;

    // wall collisions
    if (pos.x + size.x > WORLD::worldWidth || pos.x < -WORLD::worldWidth + 64.0f || pos.y < -WORLD::worldHeight - size.y + 64 || pos.y > WORLD::worldHeight)
        destroy();


    //draw
    SpriteManager::getInstance()->drawTexture("Fire_ball", pos, 
        2
        , rotation * RAD2DEG * (flipSprite? -1: 1) / 4
        , WHITE, flipSprite);
}

void Fireball::onDestroy(){
    GameObjectManager::getInstance()->addGameObject(new AnimationObject({pos.x - 4, pos.y - 4}, "FireBallExplosion_", 1, 1, 3, flipSprite));
}

void Fireball::onCollide(GameObject *other){
    if (other->getObjectIdentifier() == ObjectIdentifier::PlayerFlag){
        other->takeDamage(1, this, direction);
        destroy();
    }
}