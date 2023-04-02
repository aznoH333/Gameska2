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

        int t;
        int lifeTime;
        const int baseLifeTime = 20;
        
        const float wave_time_multiplier = 0.2f;
        const float waveMultiplier = 2.5;

    
    public:
        Bubble(Vector2 pos);
        void update();
};




#endif