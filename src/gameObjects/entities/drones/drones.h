#ifndef DRONES
#define DRONES

#include "drone.h"
#include "raylib.h"
#include "../../../sprites/SpriteManager.h"

class GunDrone : public Drone{
    public:
        GunDrone();
        void fire(Vector2 pos);
};


class ShotGunDrone : public Drone{
    public:
        ShotGunDrone();
        void fire(Vector2 pos);
};

#endif