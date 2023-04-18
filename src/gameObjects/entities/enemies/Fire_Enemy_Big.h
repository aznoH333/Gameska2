#ifndef FIRE_ENEMY_BIG
#define FIRE_ENEMY_BIG

#include "enemy.h"
#

class Fire_Enemy_Big : public Enemy{
    
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
        const float fire_spread = 0.45f;

    protected:

        float maxSpeed = 1.5f;
        void draw();
        void engageTarget(GameObject* target);

    public:
        Fire_Enemy_Big(Vector2 pos, float healthMultiplier);
}; 

#endif