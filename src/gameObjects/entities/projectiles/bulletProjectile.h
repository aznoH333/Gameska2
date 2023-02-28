#ifndef BULLET_PROJECTILE
#define BULLET_PROJECTILE

#include "../../GameObject.h"
#include "raylib.h"


class Bullet : public GameObject{
    
    private:
        float rotation;
        float damage;
        float speed;
    
    public:
        Bullet(Vector2 pos, float rotation, float damage, float speed);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
};


#endif