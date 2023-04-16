#ifndef GAME_STATE
#define GAME_STATE

#include <string>
#include <functional>
#include <vector>
#include "raylib.h"
#include "../sprites/SpriteManager.h"
#include "../gameObjects/sound_manager.h"


struct Button{
    std::string text = "placeholder";
    std::function<void()> function = [](){};
    bool is_checkbox = false;
    bool chekcbox_value = false;
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
        int currently_selected_button = 0;


        // menu constants
        const float button_offset = 70;
        const float button_x_pos = 640;
        const float button_y_pos = 500;
        
        

        // menu item scaling
        int currently_scaled_item = 0;
        float current_item_scale = 0;

        const float item_scale_speed = 0.3f;
        const float max_item_scale_bonus = 0.3f;

        // button selector stuff
        float select_icon_offset = 0;
        float desired_select_icon_offset = select_icon_offset;
        const float select_icon_offset_y = 48;
        const float select_icon_speed = 0.3f;
        const float select_icon_horizontal_speed = 10;
        const float select_icon_additional_offset = 200;
        float select_icon_pos = 0; // value between 0 and buttos.size()




        void on_button_activate(int button_index);
        void handle_item_scaling();
        void handle_player_input();
        void draw_menu_selector();
        void draw_button(int button_index);

    public:
        static UIManager* getInstance();
        void update();
        void addButton(Button button);
        void clear();
        void dispose();
};

#endif