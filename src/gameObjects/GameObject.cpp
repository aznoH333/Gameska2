#include "GameObject.h"

GameObject::GameObject(Vector2 pos, Vector2 size, ObjectIdentifier identifier, int health){
    this->pos = pos;
    this->size = size;
    this->identifier = identifier;
    this->health = health;
}


// virtual functions
void GameObject::update(){}
void GameObject::onDestroy(){}
void GameObject::onCollide(GameObject* other){}
void GameObject::onDamage(int damage, GameObject *damageDealer, float direction){}


bool GameObject::shouldDestroy(){
    return destructionMark;
}

void GameObject::destroy(){
    destructionMark = true;
}

Vector2 GameObject::getPos(){
    return pos;
}

Vector2 GameObject::getSize(){
    return size;
}

ObjectIdentifier GameObject::getObjectIdentifier(){
    return identifier;
}

float GameObject::distanceToPosition(Vector2 position){
    return std::sqrt(std::abs(pos.x - position.x) + std::abs(pos.y - position.y));
}

void GameObject::takeDamage(int damage, GameObject* damageDealer, float direction){
    health -= damage;
    onDamage(damage, damageDealer, direction);
}

int GameObject::getHealth(){
    return health;
}