#include "player.h"
#include "raylib.h"
#include <string>
#include "../../world/world.h"

Player::Player(Vector2 pos) : GameObject(pos, {28,46}, ObjectIdentifier::PlayerFlag, 100){
    spr = SpriteManager::getInstance();
    camera = CameraObject::getInstance();
}

void Player::update(){
    // movement
    if (damageStunTimer == 0) handleMovement();
    else damageStunTimer--;
    
    
    // wall collisions
    if (pos.x + 28 + velocity.x > WORLD::worldWidth) {
        velocity.x = 0;
        pos.x = WORLD::worldWidth - 28;
    }

    if (pos.x + velocity.x < -WORLD::worldWidth + 64.0f) {
        velocity.x = 0;
        pos.x = -WORLD::worldWidth + 64;
    }

    if (pos.y + velocity.y < -WORLD::worldHeight - 46 + 64) {
        velocity.y = 0;
        pos.y = -WORLD::worldHeight - 46 + 64;
    }

    if (pos.y + velocity.y > WORLD::worldHeight){
        velocity.y = 0;
        pos.y = WORLD::worldHeight;
    }
    // values
    pos.x += velocity.x;
    pos.y += velocity.y;

    
    
    camera->setCameraPos({pos.x + (velocity.x * cameraDistanceMultiplier) - 633, pos.y + (velocity.y * cameraDistanceMultiplier) - 348});

    //draw
    draw();

    
}

void Player::onDestroy(){

}

void Player::onCollide(GameObject* other){
    if (other->getObjectIdentifier() == ObjectIdentifier::EnemyFlag){
        takeDamage(1, other);
    }
}




void Player::draw(){
    
    
    if (damageStunTimer > 0){
        spr->drawTexture("player_9", pos, 2, WHITE, flipSprite);

        if      (velocity.x < -0.5f) flipSprite = false;
        else if (velocity.x > 0.5f) flipSprite = true;
        
    }else if (isMoving){
        //moving
        walkAnimationTimer--;
        if (walkAnimationTimer == 0){
            walkAnimationTimer = maxAnimationTimer;
            animationIndex = (animationIndex+1 - minAnimationFrame) % (maxAnimationFrame - minAnimationFrame) + minAnimationFrame;
        }

        if      (velocity.x < -0.5f) flipSprite = true;
        else if (velocity.x > 0.5f) flipSprite = false; 

        spr->drawTexture("player_" + std::to_string(animationIndex), pos, 2, WHITE, flipSprite);


    }else{
        // idle
        spr->drawTexture("player_1", pos, 2, WHITE, flipSprite);
    }

    
}

void Player::handleMovement(){
    isMoving = false;
    movingAlongXAxis = false;
    movingAlongYAxis = false;
    
    movementInDirection(KEY_A, -1, 0);
    movementInDirection(KEY_D, 1, 0);
    movementInDirection(KEY_W, 0, -1);
    movementInDirection(KEY_S, 0, 1);

    if (!movingAlongXAxis && velocity.x != 0){
        if (std::abs(velocity.x) > speed)
            velocity.x -= std::copysign( speed, velocity.x);
        else
            velocity.x = 0;
    }

    if (!movingAlongYAxis && velocity.y != 0){
        if (std::abs(velocity.y) > speed)
            velocity.y -= std::copysign(speed, velocity.y);
        else
            velocity.y = 0;
    }
}

void Player::movementInDirection(int key, float xMultiplier, float yMultiplier){
    if (IsKeyDown(key)){
        isMoving = true;
        velocity.x += speed * xMultiplier;
        velocity.y += speed * yMultiplier;

        // speed limits
        if (std::abs(velocity.x) > maxSpeed) {velocity.x = std::copysign(maxSpeed, velocity.x);}
        if (std::abs(velocity.y) > maxSpeed) {velocity.y = std::copysign(maxSpeed, velocity.y);}

        if (xMultiplier != 0) movingAlongXAxis = true;
        if (yMultiplier != 0) movingAlongYAxis = true;
    }
}


void Player::onDamage(GameObject* damageDealer){
    damageStunTimer = damageStunDuration;
    float direction = (std::atan2(damageDealer->getPos().x + 32 - (pos.x + 32), -(damageDealer->getPos().y  + 32 - (pos.y + 32)))) + (90 * DEG2RAD);
    velocity.x = cos(direction) * knockBackMultiplier;
    velocity.y = sin(direction) * knockBackMultiplier;
}