#ifndef WORLD
#define WORLD

#include "../../sprites/SpriteManager.h"
#include "camera.h"
#include "raylib-cpp.hpp"
#include "raylib.h"

class World{
    private:
        SpriteManager* spr;
        static World* instance;
        void drawRegion();
        CameraObject* camera;
        Vector2 cameraPos = {0,0};
    public:
        World();
        static World* getInstance();
        void update();
        void dispose();
};

#endif