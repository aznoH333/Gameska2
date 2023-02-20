#ifndef PLAYER 
#define PLAYER


#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include <raylib-cpp.hpp>
#include <cmath>
#include "../../world/world.h"

class Player : public GameObject{
    private:
        SpriteManager* spr;
        Vector2 velocity;
        float maxSpeed = 7;
        float speed = 0.5;
        const float cameraDistanceMultiplier = 3;
        bool isMoving = false;
        bool movingAlongXAxis = false;
        bool movingAlongYAxis = false;
        bool flipSprite = false;
        World* world;


        void handleMovement();
        void movementInDirection(int key, float xMultiplier, float yMultiplier);
        void draw();
    
    public:
        Player(Vector2 pos);

        void update();
        void onDestroy();
        void onCollide(GameObject* other);
};


#endif