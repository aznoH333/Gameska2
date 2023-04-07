#ifndef PICKUPS
#define PICKUPS

#include "../../GameObject.h"
#include "raylib.h"
#include "../../../sprites/SpriteManager.h"


class UpgradePickup : public GameObject{
    private:
        float zVelocity = 10;
        float z = 0;
        const float zGravity = 0.5f;
        bool isAirborne = true;
        int zIndex = 2;

        // size stuff
        float scaleModifier = 0.01;
        const float scaleModifierIncreaseSpeed = 0.02;
        
        // sign stuff
        int timer = 0;
        const int sign_offset = 48;

    public:
        UpgradePickup(Vector2 pos);
        void update();
        void onCollide(GameObject* other);
};

#endif