#include "enemy.h"
#include "../../GameObjectManager.h"


Enemy::Enemy(Vector2 pos): GameObject(pos, {28, 46}, ObjectIdentifier::EnemyFlag, 50){
    spr = SpriteManager::getInstance();
}

void Enemy::update(){
    // move
    if (target == nullptr){
        target = GameObjectManager::getInstance()->findClosestEntityWithTag(ObjectIdentifier::PlayerFlag, 3000.0f, this);
    }else {
        engageTarget(target);
    }

    

    // draw
    if (speed < 0.2f){
        spr->drawTexture("Enemy_1", {pos.x, pos.y - 4}, 2, WHITE, flipSprite);
    }
    else {
        walkAnimationTimer--;
        if (walkAnimationTimer == 0){
            walkAnimationTimer = maxAnimationTimer;
            animationIndex = (animationIndex+1 - minAnimationFrame) % (maxAnimationFrame - minAnimationFrame) + minAnimationFrame;
        }

        spr->drawTexture("Enemy_" + std::to_string(animationIndex), {pos.x, pos.y - 4}, 2, WHITE, flipSprite);

    }
}


void Enemy::engageTarget(GameObject* target){
    float distance = distanceToPosition(target->getPos());
    float direction = (std::atan2(target->getPos().x + 32 - (pos.x + 32), -(target->getPos().y  + 32 - (pos.y + 32)))) + (-90 * DEG2RAD);
    
    if (speed < 1.0f && distance > 4) speed += 0.1f;
    else if (speed > 0.1f && distance <= 4) speed -= 0.1f;
    
    pos.x += cos(direction) * speed * maxSpeed;
    pos.y += sin(direction) * speed * maxSpeed;

    flipSprite = target->getPos().x < pos.x;
}

void Enemy::onCollide(GameObject* other){
    
}

void Enemy::onDestroy(){

}

void Enemy::onDamage(GameObject* damageDealer){

}