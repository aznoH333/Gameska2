#ifndef FIREBALL
#define FIREBALL

#include "../../GameObject.h"


class Fireball : public GameObject{

    private:
        float direction;
        bool flipSprite;
        float rotation;
        const float speed = 5.5f;

    public:
        Fireball(Vector2 pos, float direction, bool flipSprite, float rotation);
        void update();
        void onCollide(GameObject* other);
        void onDestroy();
};

#endif