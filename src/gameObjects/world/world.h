#ifndef WORLD
#define WORLD

#include "../../sprites/SpriteManager.h"
#include "../GameObjectManager.h"
#include "camera.h"
#include "raylib-cpp.hpp"
#include "raylib.h"
#include <queue>




struct WorldUpdateEvent{
    int activationTimeStampInSeconds;
    Color color;
    int maxEnemyCount;
    int enemySpawnTime;
    // TODO enemy variety
};


// distance from world center to world edge
const int worldWidth = 1280;
const int worldHeight = 720;

class World{
    private:
        SpriteManager* spr;
        GameObjectManager* objMan;
        static World* instance;
        CameraObject* camera;
        Vector2 cameraPos = {0,0};
        std::queue<WorldUpdateEvent> events;


        // variables related to spawning
        float spawnTimer = 120;
        float nextEnemySpawn = 120;
        int gameTimer = 0;
        int desiredEnemyCount = 0;
        const float overpopulationTimerIncrease = 1.3f;


        // level color
        Color worldColor = {0, 0, 0, 255};
        Color desiredColor = worldColor;
        const char colorChangeSpeed = 1;
        const int colorUpdateDelay = 2;


        void updateColor();
        void changeColor(Color color);
        void updateColorValue(unsigned char* currentColorValue, unsigned char*  desiredColorValue);
        void handleWorldEvents();
        void handleEnemySpawning();

    public:
        World();
        static World* getInstance();
        void update();
        void dispose();        
};

#endif