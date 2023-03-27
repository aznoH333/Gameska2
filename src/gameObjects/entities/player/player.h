#ifndef PLAYER 
#define PLAYER


#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include <raylib-cpp.hpp>
#include <cmath>
#include <vector>
#include "../../world/camera.h"
#include "raylib.h"
#include "../drones/drone.h"

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
        const float knockBackMultiplier = 10.0f;

        // damage stuff
        int damageStunTimer = 0;
        const int damageStunDuration = 10;
        int invulnarabilityTimer = 0;

        // drone stuff
        float droneRotation = 0;
        const float droneRotationSpeed = 0.03f;
        const float droneDistance = 48.52f;
        float lastDroneScale = 0.1;
        const float droneScaleSpeed = 0.05;

        

        std::vector<Drone*> drones;


        void handleMovement();
        void movementInDirection(int key, float xMultiplier, float yMultiplier);
        void draw();
        void droneUpdate();
        float getDroneRotation(Drone* drone, Vector2 pos);
    
    public:
        Player(Vector2 pos);

        void update();
        void onDestroy();
        void onCollide(GameObject* other);
        void onDamage(int damage, GameObject* damageDealer, float direction);
        void takeDamage(int damage, GameObject* damageDealer, float direction);
        void addDrone(Drone* d);

};


#endif