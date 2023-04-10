#ifndef DRONE
#define DRONE

#include "raylib.h"
#include <string>
#include <raylib-cpp.hpp>



enum Drone_type{ 
    type_gun = 1,
    type_laser = 2,
    type_sniper = 3,
    type_shotgun = 4,
    type_rocket = 5,
    type_machinegun = 6
};


class Drone{
    private:
        Drone_type type;
        std::string sprite;
        float fireCooldown;
        int maxLevel;
        
        // upgrades
        float firerate_upgrade = 1;
        float damage_upgrade = 1;

        //values
        float coolDown = 0;

        // constants
        const float damageUpgradeBonus = 0.6f;
        const float fireRateUpgradeBonus = 0.2f;//0.07f;
        const float maxDamageBonus = 3;
        const float maxFireRateBonus = 0.2f;
        const float screenShakeMultiplier = 0.5f;

    
    protected:
        float damage;
        int level = 1;
        bool flipSprite = false;

        bool rotates;
        float range;

        float getScreenSHake();
        float get_damage();


    public:
        Drone(Drone_type type, std::string sprite, float fireCooldown, float damage, int maxLevel, bool rotates, float range);

        Drone_type get_type();
        std::string getSprite();
        void update(Vector2 position);
        virtual void fire(Vector2 position);
        
        void upgradeDamage();
        void upgradeFireRate();
        void upgradeLevel();

        bool canUpgradeDamage();
        bool canUpgradeFireRate();
        bool canUpgradeLevel();

        bool getFlipSprite();
        bool doesRotate();
        void setFlipSprite(bool flip);

        bool can_be_upgraded();

        float getRange();
};


#endif