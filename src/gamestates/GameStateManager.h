#ifndef GAME_STATE_MANAGER
#define GAME_STATE_MANAGER

#include "Gamestate.h"
#include "Game.h"
#include <map>

enum StateName{
    state_main_menu = 0,
    state_game = 1,
    state_game_over = 2,
    state_intro = 3,
    state_pause = 4,
};


class GameStateManager{
    private:
        static GameStateManager* instance;
        std::map<StateName, GameState*> states;
        StateName currentState = state_intro;
        bool exit = false;
        bool call_init = true;
        
        // transition stuff
        float transitionValue = 0;
        const float transitionSpeed = 0.05f;
        StateName nextState = currentState;
        

    public:
        GameStateManager();
        static GameStateManager* getInstance();
        void update();
        void switchState(StateName state);
        void switch_state_without_init(StateName state);
        void transitionToState(StateName state, bool call_init);
        void transitionToState(StateName state);

        void dispose();
        bool shouldGameEnd();
        void exitGame();

};

#endif