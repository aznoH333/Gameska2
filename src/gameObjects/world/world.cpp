#include "world.h"
#include "camera.h"
#include "raylib.h"
#include "../entities/enemies/enemy.h"
#include "../entities/enemies/fireEnemy.h"

#include <cmath>








World* World::getInstance(){
    if (!instance) instance = new World();
    return instance;
}

World::World(){
    spr = SpriteManager::getInstance();
    camera = CameraObject::getInstance();
    objMan = GameObjectManager::getInstance();

    //changeColor({60, 40, 99});



    // set world events

    events.push(WorldUpdateEvent{1, {40, 40, 40}, 4, 360, 1, 1});
    events.push(WorldUpdateEvent{7, {40, 65, 40}, 10, 80, 1, 1});
    events.push(WorldUpdateEvent{30, {40, 100, 40}, 15, 45, 1, 2});
    events.push(WorldUpdateEvent{45, {40, 30, 80}, 20, 60, 1, 2});
    events.push(WorldUpdateEvent{60, {100, 30, 40}, 40, 10, 1, 1}); // huge enemy wave
    events.push(WorldUpdateEvent{65, {60, 40, 40}, 20, 80, 1, 2});
    events.push(WorldUpdateEvent{90, {60, 60, 80}, 20, 40, 1, 2});






}

void World::update(){
    
    // draw world
    cameraPos = camera->getCameraPos();
    for (float x = cameraPos.x - 64; x < cameraPos.x + worldWidth + 64; x += 64){
        for (float y = cameraPos.y - 64; y < cameraPos.y + worldHeight + 64; y += 64){
            if (std::abs(x - (float)((int)cameraPos.x % 64)) < worldWidth && std::abs(y - (float)((int)cameraPos.y % 64)) < worldHeight)
                spr->drawTexture({"floor_tile", {x - (float)((int)cameraPos.x % 64), y - (float)((int)cameraPos.y % 64)}, 2, 0, worldColor, false, layer_world});
            else
                spr->drawTexture({"brick_wall", {x - (float)((int)cameraPos.x % 64), y - (float)((int)cameraPos.y % 64)}, 2, 0, worldColor, false, layer_world});

        }
    }


    gameTimer++;
    
    if (gameTimer % colorUpdateDelay == 0){
        updateColor();
    }

    handleWorldEvents();
    handleEnemySpawning();

    
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


const float framesPerSecond = 60;
void World::handleWorldEvents(){
    if (!events.empty() && gameTimer >= events.front().activationTimeStampInSeconds * framesPerSecond){
        // activate event
        WorldUpdateEvent event = events.front();

        changeColor(event.color);

        desiredEnemyCount = event.maxEnemyCount;
        nextEnemySpawn = event.enemySpawnTime;
        enemyTier = event.enemyTier;
        healthMultiplier = event.healthMultiplier;


        if (spawnTimer > nextEnemySpawn) spawnTimer = nextEnemySpawn;

        events.pop();
    }
}


void World::handleEnemySpawning(){
    //spawn enemies
    spawnTimer--;
    if (spawnTimer <= 0){
        spawnTimer = nextEnemySpawn;
        if (objMan->getObjectCountWithTag(ObjectIdentifier::EnemyFlag) > desiredEnemyCount) spawnTimer *= overpopulationTimerIncrease;
        
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


        GameObject* enemy;
        // choose enemy type
        switch (GetRandomValue(1, enemyTier)) {
            case 1:
                enemy = new Enemy({tempX, tempY}, healthMultiplier);
                break;
            case 2:
                enemy = new FireEnemy({tempX, tempY}, healthMultiplier);
                break;
        
        }
        // add enemy
        objMan->addGameObject(enemy);
    }

}

World* World::instance = 0;