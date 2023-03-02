#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include "raylib.h"

class Enemy : public GameObject{
    private:
        SpriteManager* spr;
        float maxSpeed = 3;
        float speed = 0;
        float direction = 0;
        GameObject* target = nullptr;
        bool flipSprite = false;
        int animationIndex = 2;
        int walkAnimationTimer = 1;
        const int maxAnimationTimer = 4;
        const int maxAnimationFrame = 9;
        const int minAnimationFrame = 2;

        int knockBackTimer = 0;
        const float knockBackMultiplier = 0.6;
        const float knockBackStunMultiplier = 1.1f;
        const float knockBackRecovery = 1.5f;
        float knockBackDirection = 0;
        float knockBackSpeed = 0;



        void engageTarget(GameObject* target);
        void handleKnockBack();
        float sigmaReLU(float number);

    public:
        Enemy(Vector2);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
        void onDamage(int damage, GameObject* damageDealer, float direction);

};

#endif