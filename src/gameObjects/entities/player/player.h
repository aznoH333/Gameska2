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
#include "../animationObject/particles.h"


// stored number corresponds to drone texture
// example : type_gun = 1 | Amongus_1.png



class Player : public GameObject{
    private:
        const int maxAnimationFrame = 9;
        const int minAnimationFrame = 2;
        const int maxAnimationTimer = 3;

        SpriteManager* spr;
        Vector2 velocity = {0,0};
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
        const float drone_rotation_finder_bonus = 75;

        // death related stuff
        int deathTimer = 20;
        const int deathFrameLength = 8;
        const int lastDeathFrame = 10;
        int currentDeathFrame = 1;
        int deathFrameTimer = deathFrameLength;

        
        // drone info constants
        const float drone_info_block_width = 4;
        const float drone_info_block_height = 6;
        const float drone_height = 32;


        std::vector<Drone*> drones;


        void handleMovement();
        void movementInDirection(int key, float xMultiplier, float yMultiplier);
        void draw();
        void droneUpdate();
        float getDroneRotation(Drone* drone, Vector2 pos);
        void life();
        void death();
        void display_drone_info(int drone_index, Vector2 drone_pos);

    public:
        Player(Vector2 pos);

        void update();
        void onDestroy();
        void onCollide(GameObject* other);
        void onDamage(int damage, GameObject* damageDealer, float direction);
        void takeDamage(int damage, GameObject* damageDealer, float direction);
        void addDrone(Drone_type drone_type);
        std::vector<Drone*>* get_drones(); 

};





#endif