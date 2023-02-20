#ifndef PLAYER 
#define PLAYER


#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include <raylib-cpp.hpp>

class Player : public GameObject{
    private:
        SpriteManager* spr;
        Vector2 velocity;
        float maxSpeed = 10;
        float speed = 0.5;
        float speedLoss = 1;
        bool isMoving = false;
        bool movingAlongXAxis = false;
        bool movingAlongYAxis = false;
        bool flipSprite = false;


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