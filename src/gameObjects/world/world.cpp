#include "world.h"
#include "camera.h"
#include "raylib.h"


World* World::getInstance(){
    if (!instance) instance = new World();
    return instance;
}

World::World(){
    spr = SpriteManager::getInstance();
    camera = CameraObject::getInstance();
}

void World::drawRegion(){
    
}

void World::update(){
    cameraPos = camera->getCameraPos();
    for (float x = cameraPos.x - 64; x < cameraPos.x + 1280 + 64; x += 64){
        for (float y = cameraPos.y - 64; y < cameraPos.y + 720 + 64; y += 64){
            if (std::abs(x - (float)((int)cameraPos.x % 64)) < 1280 && std::abs(y - (float)((int)cameraPos.y % 64)) < 720)
                spr->drawTexture("floor_tile", {x - (float)((int)cameraPos.x % 64), y - (float)((int)cameraPos.y % 64)}, 2, WHITE, false);
            else
                spr->drawTexture("brick_wall", {x - (float)((int)cameraPos.x % 64), y - (float)((int)cameraPos.y % 64)}, 2, WHITE, false);

        }
    }
}

void World::dispose(){
    delete instance;
}


World* World::instance = 0;