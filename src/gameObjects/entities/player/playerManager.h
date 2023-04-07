#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include <raylib-cpp.hpp>
#include "player.h"
#include "../../GameObjectManager.h"
#include "pickups.h"
#include "raylib.h"



enum Upgrade_action{
    action_replace,
    action_upgrade_damage,
    action_upgrade_fire_rate,
    action_upgrade_level,
    action_add_drone
};

struct Drone_upgrade{
    Upgrade_action action;
    int action_index;
    Drone_type type;
};




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
        int unselected_upgrade_count = 100;
        int drone_count = 1;

        // upgrade choice stuff
        std::vector<Drone_upgrade> upgrades;

        
        
        PlayerManager();
        void generate_upgrades();
        void handleUI();
        void handle_upgrade_selection();
        Upgrade_action choose_random_upgrade(Drone* drone);
        void handle_upgrade_action(KeyboardKey key, int upgrade_slot);


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