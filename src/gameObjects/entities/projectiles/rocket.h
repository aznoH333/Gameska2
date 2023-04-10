#ifndef ROCKET_PROJECTILE
#define ROCKET_PROJECTILE

#include "../../GameObject.h"
#include "raylib.h"
#include "../../../sprites/SpriteManager.h"
#include "../../world/world.h"

class Rocket : public GameObject{
    
    private:
        float damage;
        float speed;
        float acceleration_multiplier = 0.10;
        const float acceleration = 0.10f;

        bool is_exploding = false;
        int life_time = 180;
        int targeting_time = 20;

        float rotation = 270;
        const float rotation_speed = 10.0f;

        void explosion();
        void seek_target();
    
    public:
        Rocket(Vector2 pos, float damage, float speed);

        void update();
        void onCollide(GameObject* other);
        void onDestroy();
};

#endif