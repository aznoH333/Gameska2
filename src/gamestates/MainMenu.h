#ifndef MAIN_MENU
#define MAIN_MENU

#include "Gamestate.h"
#include <raylib-cpp.hpp>
#include "raylib.h"
#include "GameStateManager.h"


class MainMenu : public GameState{
    public:
        MainMenu();
        void update();
        void clear();
        void init();
};

#endif