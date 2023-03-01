#include "world.h"
#include "camera.h"
#include "raylib.h"
#include "../entities/enemies/enemy.h"
#include <cmath>


World* World::getInstance(){
    if (!instance) instance = new World();
    return instance;
}

World::World(){
    spr = SpriteManager::getInstance();
    camera = CameraObject::getInstance();
    objMan = GameObjectManager::getInstance();

    changeColor({99, 40, 37});
}

void World::update(){
    
    // draw world
    cameraPos = camera->getCameraPos();
    for (float x = cameraPos.x - 64; x < cameraPos.x + worldWidth + 64; x += 64){
        for (float y = cameraPos.y - 64; y < cameraPos.y + worldHeight + 64; y += 64){
            if (std::abs(x - (float)((int)cameraPos.x % 64)) < worldWidth && std::abs(y - (float)((int)cameraPos.y % 64)) < worldHeight)
                spr->drawTexture("floor_tile", {x - (float)((int)cameraPos.x % 64), y - (float)((int)cameraPos.y % 64)}, 2, 0, worldColor, false);
            else
                spr->drawTexture("brick_wall", {x - (float)((int)cameraPos.x % 64), y - (float)((int)cameraPos.y % 64)}, 2, 0, worldColor, false);

        }
    }


    gameTimer++;
    //spawn enemies
    spawnTimer--;
    if (spawnTimer <= 0 && objMan->getObjectCountWithTag(ObjectIdentifier::EnemyFlag) < desiredEnemyCount){
        spawnTimer = nextEnemySpawn;
        
        float tempX;
        float tempY;
        
        do {
            if (GetRandomValue(0, 1) >= 1){
                
                tempX = GetRandomValue(0, 1) * 1344 - 64 + cameraPos.x;
                tempY = GetRandomValue(0, 720) + cameraPos.y;
            }else{
                tempX = GetRandomValue(0, 1280) + cameraPos.x;
                tempY = GetRandomValue(0, 1) * 784 - 64 + cameraPos.y;
            }
            

        }while(std::abs(tempX) > worldWidth || std::abs(tempY) > worldHeight);


        objMan->addGameObject(new Enemy({tempX, tempY})); // TODO : enemy variety
    }

    if (gameTimer % 3 == 0){
        updateColor();

    }
    
}

void World::dispose(){
    delete instance;
}



void World::updateColor(){
    updateColorValue(&(worldColor.r), &(desiredColor.r));
    updateColorValue(&(worldColor.g), &(desiredColor.g));
    updateColorValue(&(worldColor.b), &(desiredColor.b));

}

void World::changeColor(Color color){
    desiredColor = color;
}


void World::updateColorValue(unsigned char* currentColorValue, unsigned char* desiredColorValue){
    if (std::abs(*(currentColorValue) - *(desiredColorValue)) <= colorChangeSpeed) 
        *(currentColorValue) = *(desiredColorValue);
    else
        *(currentColorValue) -= std::copysign( colorChangeSpeed, *(currentColorValue) - *(desiredColorValue));
}


World* World::instance = 0;