#include "GameObjectManager.h"
#include "GameObject.h"
#include "raylib.h"
#include <cmath>


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
            return true;
        }
        return false;
    });

    // check for collisions
    for (GameObject* g : objects){
        for (GameObject* other : objects){
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

void GameObjectManager::dispose(){
    for (GameObject* g : objects){
        delete g;
    }
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


int GameObjectManager::getObjectCountWithTag(ObjectIdentifier tag){
    int output = 0;
    for (GameObject* g : objects){
        if (g->getObjectIdentifier() == tag)
            output++;
    }
    return output;
}

GameObjectManager* GameObjectManager::instance = 0;
