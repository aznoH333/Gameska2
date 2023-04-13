#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include <raylib-cpp.hpp>
#include "player.h"
#include "../../GameObjectManager.h"
#include "pickups.h"
#include "raylib.h"



enum upgrade_action{
    action_replace = 6,
    action_upgrade_damage = 3,
    action_upgrade_fire_rate = 5,
    action_upgrade_level = 4,
    action_add_drone = 2
};

struct Upgrade{
    upgrade_action action;
    int action_index;
    Drone_type type;
};

const std::map<upgrade_action, std::string> upgrade_descriptions = {
    {action_replace, "replace"},
    {action_upgrade_damage, "damage up"},
    {action_upgrade_fire_rate, "fire rate up"},
    {action_upgrade_level, "level up"},
    {action_add_drone, "new drone"}
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
        int unselected_upgrade_count = 0;
        int drone_count = 1;

        // upgrade choice stuff
        std::vector<Upgrade> upgrades;


        // upgrade selection visual stuff
        const float selection_hidden = 0;
        const float selection_visible = 96;
        const float selection_gap = 124;
        const float selection_speed = 6.5f;
        
        const float drone_icon_offset = 32;
        const float upgrade_icon_offset = 0;
        
        const float selection_x = 516;
        float selection_y = selection_hidden;


        
        
        PlayerManager();
        void generate_upgrades();
        void handleUI();
        void display_upgrade_selection();
        void handle_upgrade_selection();
        upgrade_action choose_random_upgrade(Drone* drone);
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

        bool is_upgrade_selection_shown();
};



#endif