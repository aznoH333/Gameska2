#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "raylib.h"
#include <raylib-cpp.hpp>


enum ObjectIdentifier {
    EnemyFlag,
    PlayerFlag,
    PlayerProjectileFlag,
    EnemyProjectileFlag
};



class GameObject{
    private:
        bool destructionMark = false;
    
    protected:
        Vector2 pos;
        Vector2 size;
        int health;
        ObjectIdentifier identifier;
    



    public:
        GameObject(Vector2 pos, Vector2 size, ObjectIdentifier identifier, int health);
        virtual void update();
        virtual void onDestroy();
        virtual void onCollide(GameObject* other);
        virtual void onDamage(int damage, GameObject* damageDealer, float direction);
        bool shouldDestroy();
        void destroy();
        Vector2 getPos();
        Vector2 getSize();
        float distanceToPosition(Vector2 position);
        ObjectIdentifier getObjectIdentifier();
        void takeDamage(int damage, GameObject* damageDealer, float direction);

};

#endif