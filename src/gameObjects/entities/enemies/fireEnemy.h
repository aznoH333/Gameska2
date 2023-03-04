#ifndef FIRE_ENEMY
#define FIRE_ENEMY

#include "enemy.h"

class FireEnemy : public Enemy{
    


    protected:
        void draw();
        void engageTarget(GameObject* target);

    public:
        FireEnemy(Vector2 pos, float healthMultiplier);
}; 

#endif