#include "enemy.h"


Enemy::Enemy(Vector2 pos): GameObject(pos, {28, 50}, ObjectIdentifier::EnemyFlag){
    spr = SpriteManager::getInstance();
}

void Enemy::update(){
    spr->drawTexture("Enemy_1", pos, 2, WHITE, false);
}

void Enemy::onCollide(GameObject* other){

}

void Enemy::onDestroy(){

}