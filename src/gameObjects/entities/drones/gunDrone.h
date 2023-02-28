#ifndef GUN_DRONE
#define GUN_DRONE

#include "drone.h"
#include "raylib.h"

class GunDrone : public Drone{
    public:
        GunDrone();
        void fire(Vector2 pos);
};

#endif