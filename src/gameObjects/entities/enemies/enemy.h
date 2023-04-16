#ifndef ENEMY_OBJECT
#define ENEMY_OBJECT

#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include "raylib.h"
#include "../player/playerManager.h"
#include "../animationObject/blood.h"
#include "../../sound_manager.h"
#include "../../Settings_Manager.h"

class Enemy : public GameObject{
    protected:
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

        const float knockBackMultiplier = 0.6;
        const float knockBackStunMultiplier = 1.1f;
        const float knockBackRecovery = 1.5f;
        float knockBackDirection = 0;
        float knockBackSpeed = 0;
        const float max_knockback_speed = 30;

        // gore
        const int goreOffsetX = -16;
        const int goreOffsetY = -8;


        void handleKnockBack();
        float sigmaReLU(float number);
        void worldCollisions();

        virtual void engageTarget(GameObject* target);
        virtual void draw();
        int knockBackTimer = 0;
        void handle_gore(int damage);



    public:
        Enemy(Vector2, float healthMultiplier);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
        void onDamage(int damage, GameObject* damageDealer, float direction);

};

#endif