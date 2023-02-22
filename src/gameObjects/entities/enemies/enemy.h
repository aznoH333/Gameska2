#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"

class Enemy : public GameObject{
    private:
        SpriteManager* spr;
        float maxSpeed = 3;
        float speed = 0;
        GameObject* target = nullptr;
        bool flipSprite = false;
        int animationIndex = 2;
        int walkAnimationTimer = 1;
        const int maxAnimationTimer = 4;
        const int maxAnimationFrame = 9;
        const int minAnimationFrame = 2;


        void engageTarget(GameObject* target);

    public:
        Enemy(Vector2);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
        void onDamage(GameObject* damageDealer);

};

#endif