#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"

class Enemy : public GameObject{
    private:
        SpriteManager* spr;
        float maxSpeed = 3;
        float speed = 0;

    public:
        Enemy(Vector2);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
};

#endif