#ifndef WORLD
#define WORLD

#include "../../sprites/SpriteManager.h"
#include "../GameObjectManager.h"
#include "camera.h"
#include "raylib-cpp.hpp"
#include "raylib.h"



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

        // variables related to spawning
        float spawnTimer = 120;
        float nextEnemySpawn = 60;
        int gameTimer = 0;
        int desiredEnemyCount = 5;



    public:
        World();
        static World* getInstance();
        void update();
        void dispose();        
};

#endif