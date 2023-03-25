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

        // text constants
        const float fontsize = 60;
        const float shadow_offset = 4.66;
        const float button_offset = 70;
        const float button_x_pos = 544;
        const float button_y_pos = 360;
        const float menu_select_icon_offset = -60;
        const float menu_select_icon_offset_y = 48;
        const float menu_select_icon_offset_right = 256;


        void drawText(std::string text, float x, float y);

    public:
        static UIManager* getInstance();
        void update();
        void addButton(Button button);
        void clear();
        void dispose();
};

#endif