#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include <raylib-cpp.hpp>
#include "player.h"

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
        

        
        
        PlayerManager();

        void handleUI();


    public:
        static PlayerManager* getInstance();
        void update();
        void dispose();
        void registerPlayerObject(Player* player);
        void removePlayer();
};



#endif