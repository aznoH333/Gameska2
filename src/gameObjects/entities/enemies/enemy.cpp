#include "enemy.h"
#include "../../GameObjectManager.h"
#include "../../sound_manager.h"
#include <cmath>
#include <string>
#include "../../world/world.h"
#include "../animationObject/animationObject.h"

Enemy::Enemy(Vector2 pos, float healthMultiplier): GameObject(pos, {28, 46}, ObjectIdentifier::EnemyFlag, 50 * healthMultiplier){
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

    draw();
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

    // gore
    int temp = GetRandomValue(0, 1) * 5 + 1;
    GameObjectManager::getInstance()->addGameObject(new AnimationObject(
    {pos.x + goreOffsetX, pos.y + goreOffsetY}
    , "Gore_", temp, temp+4, 4, flipSprite));


    // progress related stuff
    PlayerManager::getInstance()->confirmKill(pos);
}

void Enemy::onDamage(int damage, GameObject* damageDealer, float direction){
    
    if (health <= 0) destroy();
    
    handle_gore(damage);
    
    
    knockBackDirection = direction;
    knockBackTimer = std::min(damage * knockBackStunMultiplier,max_knockback_speed);
    knockBackSpeed = std::min(damage * knockBackMultiplier, max_knockback_speed);
    speed = 0;
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


void Enemy::draw(){
    if (knockBackTimer >0){
        spr->drawTexture({"Enemy_9", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite, layer_enemy});
    }else if (speed < 0.2f){
        spr->drawTexture({"Enemy_1", {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite, layer_enemy});
    }
    else {
        walkAnimationTimer--;
        if (walkAnimationTimer == 0){
            walkAnimationTimer = maxAnimationTimer;
            animationIndex = (animationIndex+1 - minAnimationFrame) % (maxAnimationFrame - minAnimationFrame) + minAnimationFrame;
        }

        spr->drawTexture({"Enemy_" + std::to_string(animationIndex), {pos.x, pos.y - 4}, 2, 0, WHITE, flipSprite, layer_enemy});

    }
}

void Enemy::handle_gore(int damage){
    
    // spawn blood
    for (int i = std::min(damage / 5, 10); i > 0; i--){
        GameObjectManager::getInstance()->addGameObject(new Blood({pos.x + GetRandomValue(0, size.x), pos.y + size.y}, type_blood));
    }
    // spawn giblets
    if (health <= 0){
        Sound_manager::get_instance()->play_sound("Roztylska_3");
        
        for (int i = GetRandomValue(1, 4); i > 0; i--){
            GameObjectManager::getInstance()->addGameObject(new Blood({pos.x + GetRandomValue(0, size.x), pos.y + size.y}, type_giblet));
        }
        // spawn big blood
        if (damage > 25 || GetRandomValue(0, 1) > 0){
            GameObjectManager::getInstance()->addGameObject(new Blood({pos.x + GetRandomValue(0, size.x), pos.y + size.y}, type_blood_big));
        }
    }
}