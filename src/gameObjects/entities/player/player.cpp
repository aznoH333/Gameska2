#include "player.h"
#include "raylib.h"
#include <cmath>


Player::Player(Vector2 pos) : GameObject(pos, {64,64}, ObjectIdentifier::PlayerFlag){
    spr = SpriteManager::getInstance();
    
}

void Player::update(){
    // movement
    handleMovement();
    // values
    pos.x += velocity.x;
    pos.y += velocity.y;

    //draw
    draw();

    
}

void Player::onDestroy(){

}

void Player::onCollide(GameObject* other){

}

void Player::draw(){
    spr->drawTexture("player_1", pos, 2, WHITE);
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
        if (std::abs(velocity.x) > speedLoss)
            velocity.x -= std::copysign( speedLoss, velocity.x);
        else
            velocity.x = 0;
    }

    if (!movingAlongYAxis && velocity.y != 0){
        if (std::abs(velocity.y) > speedLoss)
            velocity.y -= std::copysign(speedLoss, velocity.y);
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