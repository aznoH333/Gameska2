#ifndef MISC_STATES
#define MISC_STATES

#include "Gamestate.h"
#include "../sprites/SpriteManager.h"
#include "GameStateManager.h"

class Intro : public GameState{
    private:
        int introTimer = 120;
        const float logoX = 456;
        const float logoY = 150;

    public:
        void update();
};

class GameOver : public GameState{
    public:
        void init();
        void update();
        void clear();
};


#endif