#ifndef GAME_STATE
#define GAME_STATE

#include <string>
#include <functional>
#include <vector>
#include "raylib.h"
#include "../sprites/SpriteManager.h"


struct Button{
    std::string text = "placeholder";
    std::function<void()> function = [](){};
};

class GameState{
    public:
        virtual void update();
        virtual void clear();
        virtual void init();
};


class UIManager{
    private:
        static UIManager* instance;
        std::vector<Button> buttons;
        int currentlySelectedButton = 0;


        // menu constants
        const float button_offset = 70;
        const float button_x_pos = 544;
        const float button_y_pos = 500;
        const float menu_select_icon_offset = -60;
        const float menu_select_icon_offset_y = 48;
        const float menu_select_icon_offset_right = 256;

        // menu item scaling
        int currently_scaled_item = 0;
        float current_item_scale = 0;

        const float item_scale_speed = 0.3f;
        const float max_item_scale_bonus = 0.3f;

    public:
        static UIManager* getInstance();
        void update();
        void addButton(Button button);
        void clear();
        void dispose();
};

#endif