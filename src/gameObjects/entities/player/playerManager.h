#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include <raylib-cpp.hpp>
#include "player.h"
#include "../../GameObjectManager.h"
#include "pickups.h"
#include "../drones/drones.h"

class PlayerManager{
    private:
        static PlayerManager* instance;
        
        // dumb constants for hud visuals
        const float hudWidth = 256;
        const float hudClosed = 768;
        const float hudOpen = 720;
        const float healthOffsetX = 48;
        const float healthOffsetY = 8;

        // other hud stuff
        Vector2 hudPosition = {768,hudClosed};
        float desiredHudY = hudOpen;
        const float hudSpeed = 0.5f;
        Player* playerObject = nullptr;
        const int maxPlayerHP = 5;
        
        // weapon progression stuff
        int upgradeCount = 0;
        int nextUpgradeCount = 5;
        int killCounter = 0;

        
        
        PlayerManager();

        void handleUI();


    public:
        static PlayerManager* getInstance();
        void update();
        void dispose();
        void registerPlayerObject(Player* player);
        void removePlayer();
        void touchedUpgradeBox();
        void reset();
        void confirmKill(Vector2 pos);
};



#endif