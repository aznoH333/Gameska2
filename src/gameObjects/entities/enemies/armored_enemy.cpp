#include "armored_enemy.h"
#include "enemy.h"
#include "../../GameObjectManager.h"


void Armored_Enemy::draw(){
    if (knockBackTimer >0){
        spr->drawTexture({"armored_enemy_9", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite, layer_enemy});
    }else if (speed < 0.2f){
        spr->drawTexture({"armored_enemy_1", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite, layer_enemy});
    }
    else {
        walkAnimationTimer--;
        if (walkAnimationTimer == 0){
            walkAnimationTimer = maxAnimationTimer;
            animationIndex = (animationIndex+1 - minAnimationFrame) % (maxAnimationFrame - minAnimationFrame) + minAnimationFrame;
        }

        spr->drawTexture({"armored_enemy_" + std::to_string(animationIndex), {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite, layer_enemy});

    }

}

Armored_Enemy::Armored_Enemy(Vector2 pos, float healthMultiplier): Enemy(pos, healthMultiplier * 3.5f){}

void Armored_Enemy::engageTarget(GameObject* target){
    direction = (std::atan2(target->getPos().x + 32 - (pos.x + 32), -(target->getPos().y  + 32 - (pos.y + 32)))) + (-90 * DEG2RAD);
    
    float distance = distanceToPosition(target->getPos());
        
    if (speed < 1.0f && distance > 4) speed += 0.1f;
    else if (speed > 0.1f && distance <= 4) speed -= 0.1f;
        
    pos.x += cos(direction) * speed * maxSpeed;
    pos.y += sin(direction) * speed * maxSpeed;


    flipSprite = target->getPos().x < pos.x;

    
}