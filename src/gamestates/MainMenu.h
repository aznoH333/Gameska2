#ifndef MAIN_MENU
#define MAIN_MENU

#include "Gamestate.h"
#include <raylib-cpp.hpp>
#include <vector>




class MainMenu : public GameState{
    private:
        std::vector<Button> buttons;
    public:
        void update();
        void clear();
        void init();
};

#endif