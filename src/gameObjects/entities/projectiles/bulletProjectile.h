#ifndef BULLET_PROJECTILE
#define BULLET_PROJECTILE

#include "../../GameObject.h"
#include "raylib.h"


enum projectile_look{
    projectile_bullet,
    projectile_laser,
};


class Bullet : public GameObject{
    
    private:
        float rotation;
        float damage;
        float speed;
        int spawnTimer = 30;
        projectile_look look;
    
    public:
        Bullet(Vector2 pos, float rotation, float damage, float speed, projectile_look appearance);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
};


#endif