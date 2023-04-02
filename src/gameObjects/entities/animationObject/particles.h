#ifndef PARTICLE 
#define PARTICLE

#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include "raylib.h"


class Bubble : public GameObject{
    private:
        float scale = 0.01f;
        float rotation = 0;
        const float speed = 1.7f;
        const float waveMultiplier = 30;

        int t;
        int lifeTime;
        const int baseLifeTime = 20;
    
    public:
        Bubble(Vector2 pos);
        void update();
};




#endif