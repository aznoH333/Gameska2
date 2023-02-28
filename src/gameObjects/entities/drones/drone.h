#ifndef DRONE
#define DRONE

#include "raylib.h"
#include <string>
#include <raylib-cpp.hpp>
class Drone{
    private:
        std::string name;
        std::string sprite;
        int fireCooldown;
        
        int maxLevel;
        
        // upgrades
        float fireRateUpgrade = 1;
        float damageUpgrade = 1;

        //values
        int coolDown = 0;
        bool flipSprite = false;

        // constants
        const float damageUpgradeBonus = 0.07f;
        const float fireRateUpgradeBonus = 0.07f;
        const float maxDamageBonus = 3;
        const float maxFireRateBonus = 0.5f;

    
    protected:
        float damage;
        int level = 1;

    public:
        Drone(std::string name, std::string sprite, int fireCooldown, float damage, int maxLevel);

        std::string getName();
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
};


#endif