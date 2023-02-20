#include "world.h"

World* World::getInstance(){
    if (!instance) instance = new World();
    return instance;
}


void World::dispose(){
    delete instance;
}

void World::setCameraPos(Vector2 pos){
    cameraPos = pos;
}

Vector2 World::getCameraPos(){
    return cameraPos;
}

World* World::instance = 0;