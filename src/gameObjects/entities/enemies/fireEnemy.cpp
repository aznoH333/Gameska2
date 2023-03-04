#include "fireEnemy.h"
#include "enemy.h"


void FireEnemy::draw(){
    if (knockBackTimer >0){
        spr->drawTexture("Fire_Enemy_9", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite);
    }else if (speed < 0.2f){
        spr->drawTexture("Fire_Enemy_1", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite);
    }
    else {
        walkAnimationTimer--;
        if (walkAnimationTimer == 0){
            walkAnimationTimer = maxAnimationTimer;
            animationIndex = (animationIndex+1 - minAnimationFrame) % (maxAnimationFrame - minAnimationFrame) + minAnimationFrame;
        }

        spr->drawTexture("Fire_Enemy_" + std::to_string(animationIndex), {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite);

    }
}

FireEnemy::FireEnemy(Vector2 pos, float healthMultiplier): Enemy(pos, healthMultiplier * 0.8f){}

void FireEnemy::engageTarget(GameObject* target){
    float distance = distanceToPosition(target->getPos());
    direction = (std::atan2(target->getPos().x + 32 - (pos.x + 32), -(target->getPos().y  + 32 - (pos.y + 32)))) + (-90 * DEG2RAD);
    
    if (speed < 1.0f && distance > 4) speed += 0.1f;
    else if (speed > 0.1f && distance <= 4) speed -= 0.1f;
    
    pos.x += cos(direction) * speed * maxSpeed;
    pos.y += sin(direction) * speed * maxSpeed;

    flipSprite = target->getPos().x < pos.x;
}