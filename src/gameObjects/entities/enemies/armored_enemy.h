#ifndef ARMORED_ENEMY
#define ARMORED_ENEMY

#include "enemy.h"
#

class Armored_Enemy : public Enemy{
    
    private:
        

    protected:

        float maxSpeed = 2.5f;
        void draw();
        void engageTarget(GameObject* target);

    public:
        Armored_Enemy(Vector2 pos, float healthMultiplier);
}; 

#endif