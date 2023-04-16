#ifndef MISC_STATES
#define MISC_STATES

#include "Gamestate.h"
#include "../sprites/SpriteManager.h"
#include "GameStateManager.h"
#include "raylib.h"
#include "../gameObjects/Settings_Manager.h"

class Intro : public GameState{
    private:
        int introTimer = 120;
        const float logoX = 456;
        const float logoY = 150;

    public:
        void update();
        void clear();
};

class Game_Over : public GameState{
    private:
        const Vector2 game_over = {400, 100};
        const Vector2 survived_text = {450, 200};
        const Vector2 survived_timer = {580,300};

        std::string survived_time = "";

    public:
        void init();
        void update();
        void clear();
};

class Pause_Menu : public GameState{
    public:
        void init();
        void update();
        void clear();
};


class Options_Menu : public GameState{
    private:
        const float backdrop_speed = 0.2f;
        float backdrop_offset = 0;

    public:
        void init();
        void update();
        void clear();
};


#endif