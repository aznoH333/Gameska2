#include "world.h"
#include "camera.h"
#include "raylib.h"
#include "../entities/enemies/enemy.h"
#include "../entities/enemies/fireEnemy.h"
#include "../entities/enemies/Fire_Enemy_Big.h"
#include "../entities/enemies/armored_enemy.h"



#include <cmath>
#include <string>








World* World::getInstance(){
    if (!instance) instance = new World();
    return instance;
}

World::World(){
    spr = SpriteManager::getInstance();
    camera = CameraObject::getInstance();
    objMan = GameObjectManager::getInstance();

    //changeColor({60, 40, 99});
    loadEvents();
}

void World::loadEvents(){
    events = {};

    // set world events
    
    // easy intro
    events.push({1, {40, 40, 40}, 4, 360, 0.5f, 1});
    events.push({20, {65, 40, 40}, 7, 120, 0.6f, 1});
    events.push({35, {75, 40, 40}, 7, 120, 0.6f, 1});
    events.push({50, {65, 50, 50}, 15, 90, 0.7f, 1});


    // first big wave
    events.push({70, {100, 20, 20}, 20, 20, 1.0f, 1});
    events.push({75, {20, 20, 20}, 10, 90, 1.0f, 1});


    // blue time
    events.push({90, {40, 40, 60}, 20, 80, 1.0f, 1});
    events.push({100, {40, 40, 80}, 25, 80, 1.0f, 2});
    events.push({130, {40, 40, 90}, 25, 60, 1.0f, 2});

    // big blue wave
    events.push({160, {50, 50, 120}, 35, 10, 1.0f, 2});
    events.push({165, {50, 50, 60}, 20, 60, 1.1f, 1});


    // teal time
    events.push({180, {40, 60, 60}, 20, 60, 1.1f, 2});
    events.push({200, {40, 80, 80}, 25, 60, 1.2f, 2});
    events.push({230, {40, 90, 90}, 25, 40, 1.3f, 2});


    // purple time - endurance
    events.push({260, {60, 40, 60}, 30, 50, 1.3f, 2});
    events.push({280, {60, 40, 80}, 30, 50, 1.5f, 2});
    events.push({320, {60, 40, 90}, 35, 30, 1.3f, 2});

    // tier 3 introduction
    events.push({350, {60, 60, 60}, 20, 60, 1.3, 2});
    events.push({360, {60, 60, 70}, 20, 60, 1.4, 3});
    events.push({380, {50, 50, 100}, 30, 60, 1.4, 3});

    events.push({390, {50, 50, 50}, 20, 80, 1.4, 3});
    events.push({400, {120, 100, 100}, 30, 30, 1.4, 3});
    events.push({410, {80, 60, 60}, 30, 30, 1.5, 2});


    events.push({440, {70, 90, 90}, 20, 60, 1.5f, 3});
    events.push({460, {70, 110, 110}, 25, 60, 1.5f, 3});
    events.push({480, {70, 120, 120}, 25, 40, 1.6f, 3});

    events.push({500, {60, 100, 60}, 30, 50, 1.6f, 4});
    events.push({530, {60, 100, 80}, 30, 50, 2, 4});
    events.push({560, {60, 100, 90}, 35, 30, 1.6f, 4});
   
    events.push({590, {20, 20, 20}, 20, 80, 1.6f, 1});
    events.push({600, {100, 20, 20}, 60, 10, 2.0f, 1});
    events.push({605, {100, 20, 20}, 10, 100, 2.0f, 1});

    events.push({630, {100, 80, 20}, 35, 30, 2.0f, 4});


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
    display_timer();
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
            case 3:
                enemy = new Fire_Enemy_Big({tempX, tempY}, healthMultiplier);
                break;
            case 4:
                enemy = new Armored_Enemy({tempX, tempY}, healthMultiplier);
                break;
        
        }
        // add enemy
        objMan->addGameObject(enemy);
    }

}

void World::reset(){
    spawnTimer = 120;
    nextEnemySpawn = 120;
    gameTimer = 0;
    desiredEnemyCount = 0;
    healthMultiplier = 1;
    enemyTier = 1;
    worldColor = {0, 0, 0 ,255};
    desiredColor = worldColor;
    loadEvents();
}

void World::display_timer(){
    int time_in_seconds = (gameTimer/60)%60;
    int time_in_minutes = gameTimer/60/60;
    std::string clock_adder = " : ";
    if (time_in_seconds < 10) clock_adder += "0";
    
    SpriteManager::getInstance()->drawText(std::to_string(time_in_minutes) + clock_adder + std::to_string(time_in_seconds), timer_x, timer_y);
}


int World::get_time_minutes(){
    return gameTimer/60/60;
}

int World::get_time_seconds(){
    return (gameTimer/60)%60;
}

World* World::instance = 0;