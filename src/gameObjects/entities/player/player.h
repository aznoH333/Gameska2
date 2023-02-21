#ifndef PLAYER 
#define PLAYER


#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include <raylib-cpp.hpp>
#include <cmath>
#include "../../world/camera.h"
#include "raylib.h"

class Player : public GameObject{
    private:
        const int maxAnimationFrame = 9;
        const int minAnimationFrame = 2;
        const int maxAnimationTimer = 3;

        SpriteManager* spr;
        Vector2 velocity;
        float maxSpeed = 7;
        float speed = 0.5;
        const float cameraDistanceMultiplier = 5;
        bool isMoving = false;
        bool movingAlongXAxis = false;
        bool movingAlongYAxis = false;
        bool flipSprite = false;
        CameraObject* camera;
        int animationIndex = 1;
        int walkAnimationTimer = 1;


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