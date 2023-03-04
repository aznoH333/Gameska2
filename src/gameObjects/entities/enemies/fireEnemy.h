#ifndef FIRE_ENEMY
#define FIRE_ENEMY

#include "enemy.h"

class FireEnemy : public Enemy{
    
    private:
        // summoning related variables
        int summoningCooldown = 60;
        const int maxSummoningCooldown = 180;
        int summoningProgress = 0;
        const int maxSummoningProgress = 60;
        bool isSummoning = false;

        const int fireBallOffsetY = 20;
        const int fireBallOffsetX = 4;
        const int summoningFlicker = 4;

    protected:

        float maxSpeed = 2.5f;
        void draw();
        void engageTarget(GameObject* target);

    public:
        FireEnemy(Vector2 pos, float healthMultiplier);
}; 

#endif