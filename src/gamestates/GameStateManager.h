#ifndef GAME_STATE_MANAGER
#define GAME_STATE_MANAGER

#include "Gamestate.h"
#include <map>

enum StateName{
    MainMenu = 0,
    Game = 1,
    GameOver = 2,
};


class GameStateManager{
    private:
        static GameStateManager* instance;
        std::map<StateName, GameState*> states;
        StateName currentState = MainMenu;

    public:
        GameStateManager();
        static GameStateManager* getInstance();
        void update();
        void switchState(StateName state);
        void dispose();

};

#endif