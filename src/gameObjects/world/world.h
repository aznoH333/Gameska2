#ifndef WORLD
#define WORLD

#include "raylib.h"
#include <raylib-cpp.hpp>

class World{
    private:
        Vector2 cameraPos = {};
        static World* instance;


    public:
        void setCameraPos(Vector2 pos);
        Vector2 getCameraPos();
        static World* getInstance();
};

#endif