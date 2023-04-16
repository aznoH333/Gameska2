#ifndef DRONES
#define DRONES

#include "drone.h"
#include "raylib.h"
#include "../../../sprites/SpriteManager.h"
#include "../../sound_manager.h"


class Gun_drone : public Drone{
    public:
        Gun_drone();
        void fire(Vector2 pos);
};


class Shotgun_drone : public Drone{
    public:
        Shotgun_drone();
        void fire(Vector2 pos);
};


class Machinegun_drone: public Drone{
    public:
        Machinegun_drone();
        void fire(Vector2 pos);
};

class Laser_drone: public Drone{
    public:
        Laser_drone();
        void fire(Vector2 pos);
};

class Rocket_drone: public Drone{
    public:
        Rocket_drone();
        void fire(Vector2 pos);
};


class Sniper_drone: public Drone{
    public:
        Sniper_drone();
        void fire(Vector2 pos);
};

#endif