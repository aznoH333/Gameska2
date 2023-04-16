#include "GameObjectManager.h"
#include "GameObject.h"
#include "raylib.h"
#include <cmath>
#include <iostream>


GameObjectManager* GameObjectManager::getInstance(){
    if (!instance) instance = new GameObjectManager();
    return instance;
}


void GameObjectManager::update(){
    
    // update and destroy
    objects.remove_if([](GameObject* g){
        g->update();
        if (g->shouldDestroy()){
            g->onDestroy();
            delete g;
            return true;
        }
        return false;
    });

    // check for collisions
    for (GameObject* g : objects){
        for (GameObject* other : objects){
            
            if (g->getSize().x > 0 && other->getSize().x > 0){
                Vector2 pos = g->getPos();
                Vector2 size = g->getSize();
                Vector2 otherPos = other->getPos();
                Vector2 otherSize = other->getSize();
                
                if (g != other &&
                pos.x + size.x > otherPos.x &&
                pos.x < otherPos.x + otherSize.x &&
                pos.y + size.y > otherPos.y &&
                pos.y < otherPos.y + otherSize.y)
                g->onCollide(other);
            }
            
            
        }
    }

}

void GameObjectManager::dispose(){
    clear();
    delete instance;
}


void GameObjectManager::addGameObject(GameObject* object){
    objects.push_back(object);
}


GameObject* GameObjectManager::findClosestEntityWithTag(ObjectIdentifier tag, float maxSearchDistance, GameObject* searchingObject){
    GameObject* output = nullptr;
    float distanceToOutput = maxSearchDistance + 1;

    for (GameObject* g : objects){
        if (g != searchingObject && g->getObjectIdentifier() == tag){
            float distance = searchingObject->distanceToPosition(g->getPos());

            if (distance < distanceToOutput){
                output = g;
                distanceToOutput = distance;
            }
        }
    }

    if (distanceToOutput > maxSearchDistance) return nullptr;
    return output;
}

GameObject* GameObjectManager::findClosestEntityWithTag(ObjectIdentifier tag, float maxSearchDistance, Vector2 startingPos){
    GameObject* output = nullptr;
    float distanceToOutput = maxSearchDistance + 1;

    for (GameObject* g : objects){
        if (g->getObjectIdentifier() == tag){
            float distance = std::sqrt(std::abs(powf(g->getPos().x - startingPos.x, 2 )) + std::abs(powf(g->getPos().y - startingPos.y, 2.0f)));

            if (distance < distanceToOutput){
                output = g;
                distanceToOutput = distance;
            }
        }
    }

    if (distanceToOutput > maxSearchDistance) return nullptr;
    return output;
}


int GameObjectManager::getObjectCountWithTag(ObjectIdentifier tag){
    int output = 0;
    for (GameObject* g : objects){
        if (g->getObjectIdentifier() == tag)
            output++;
    }
    return output;
}

float GameObjectManager::getRotationTowarsObject(Vector2 origin, Vector2 target){
    return (std::atan2(target.x + 32 - (origin.x + 16), -(target.y  + 32 - (origin.y + 16)))) + (-90 * DEG2RAD);
}

void GameObjectManager::clear(){
    // destroy
    objects.remove_if([](GameObject* g){
        g->onDestroy();
        delete g;
        return true;
    });
    
}


GameObjectManager* GameObjectManager::instance = 0;
