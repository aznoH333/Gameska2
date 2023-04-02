#ifndef MAIN_MENU
#define MAIN_MENU

#include "Gamestate.h"
#include <raylib-cpp.hpp>
#include "raylib.h"
#include "GameStateManager.h"


class MainMenu : public GameState{
    private:
        float backdrop_offset = 0;
        const float backdrop_speed = 0.2f;

    public:
        MainMenu();
        void update();
        void clear();
        void init();
};

#endif