#include "enemy.h"
#include "../../GameObjectManager.h"
#include <cmath>
#include <string>
#include "../../world/world.h"

Enemy::Enemy(Vector2 pos): GameObject(pos, {28, 46}, ObjectIdentifier::EnemyFlag, 50){
    spr = SpriteManager::getInstance();
}

void Enemy::update(){
    // move
    if (knockBackTimer > 0){
        handleKnockBack();
    }else if (target == nullptr){
        target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::PlayerFlag, 3000.0f, this);
    }else {
        engageTarget(target);
    }

    worldCollisions();

    // draw
    if (knockBackTimer >0){
        spr->drawTexture("Enemy_9", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite);
    }else if (speed < 0.2f){
        spr->drawTexture("Enemy_1", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite);
    }
    else {
        walkAnimationTimer--;
        if (walkAnimationTimer == 0){
            walkAnimationTimer = maxAnimationTimer;
            animationIndex = (animationIndex+1 - minAnimationFrame) % (maxAnimationFrame - minAnimationFrame) + minAnimationFrame;
        }

        spr->drawTexture("Enemy_" + std::to_string(animationIndex), {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite);

    }
}


void Enemy::engageTarget(GameObject* target){
    float distance = distanceToPosition(target->getPos());
    direction = (std::atan2(target->getPos().x + 32 - (pos.x + 32), -(target->getPos().y  + 32 - (pos.y + 32)))) + (-90 * DEG2RAD);
    
    if (speed < 1.0f && distance > 4) speed += 0.1f;
    else if (speed > 0.1f && distance <= 4) speed -= 0.1f;
    
    pos.x += cos(direction) * speed * maxSpeed;
    pos.y += sin(direction) * speed * maxSpeed;

    flipSprite = target->getPos().x < pos.x;
}

void Enemy::onCollide(GameObject* other){
    if (other->getObjectIdentifier() == ObjectIdentifier::PlayerFlag){
        other->takeDamage(1, this, direction);
    }else if (other->getObjectIdentifier() == ObjectIdentifier::EnemyFlag){
        // push away other enemies

        Vector2 tempooraryPushForce {
            (pos.x - other->getPos().x)*0.025f,
            (pos.y - other->getPos().y)*0.025f
        };

        pos.x += tempooraryPushForce.x;
        pos.y += tempooraryPushForce.y;

        other->setPos({
            other->getPos().x - tempooraryPushForce.x,
            other->getPos().y - tempooraryPushForce.y
        });
    }
}

void Enemy::onDestroy(){

}

void Enemy::onDamage(int damage, GameObject* damageDealer, float direction){
    
    if (health <= 0) destroy();
    knockBackDirection = direction;
    knockBackTimer = damage * knockBackStunMultiplier;
    knockBackSpeed = damage * knockBackMultiplier;
}


void Enemy::handleKnockBack(){
    // todo collisions with map
    knockBackTimer--;
    if (knockBackSpeed > 0){
        knockBackSpeed -= knockBackRecovery;
    }

    if (std::abs(pos.x + (size.x * sigmaReLU(std::cos(knockBackDirection))) + std::cos(knockBackDirection) * knockBackSpeed) < WORLD::worldWidth){
        pos.x += std::cos(knockBackDirection) * knockBackSpeed;
    }

    if (std::abs(pos.y + (size.y * sigmaReLU(std::sin(knockBackDirection))) + std::sin(knockBackDirection) * knockBackSpeed) < WORLD::worldHeight){
        pos.y += std::sin(knockBackDirection) * knockBackSpeed;
    }
}

float Enemy::sigmaReLU(float number){
    if (number <= 0) return 0;
    return 1;
}


void Enemy::worldCollisions(){
    // wall collisions
    if (pos.x + size.x > WORLD::worldWidth) {
        pos.x = WORLD::worldWidth - 28;
    }

    if (pos.x < -WORLD::worldWidth + 64.0f) {
        pos.x = -WORLD::worldWidth + 64;
    }

    if (pos.y < -WORLD::worldHeight - size.y + 64) {
        pos.y = -WORLD::worldHeight - size.y + 64;
    }

    if (pos.y > WORLD::worldHeight){
        pos.y = WORLD::worldHeight;
    }
}