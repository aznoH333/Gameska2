#ifndef GAMEOBJECT_MANAGER
#define GAMEOBJECT_MANAGER

#include "GameObject.h"
#include "raylib.h"
#include <list>

class GameObjectManager{
    private:
        static GameObjectManager* instance;
        std::list<GameObject*> objects;


    public:
        static GameObjectManager* getInstance();
        void update();
        void addGameObject(GameObject* object);
        void dispose();
        GameObject* findClosestEntityWithTag(ObjectIdentifier tag, float maxSearchDistance, GameObject* searchingObject);
        GameObject* findClosestEntityWithTag(ObjectIdentifier tag, float maxSearchDistance, Vector2 startingPos);
        float getRotationTowarsObject(Vector2 origin, Vector2 target);
        int getObjectCountWithTag(ObjectIdentifier tag);
        void clear();
};

#endif