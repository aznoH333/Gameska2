#ifndef GAME 
#define GAME 
#include "Gamestate.h"
#include "../gameObjects/GameObjectManager.h"
#include "../gameObjects/entities/player/player.h"
#include "../sprites/SpriteManager.h"
#include "../gameObjects/GameObjectManager.h"
#include "../gameObjects/world/camera.h"
#include "../gameObjects/entities/player/playerManager.h"
#include "../gameObjects/world/world.h"
#include "../gameObjects/world/camera.h"



class Game : public GameState{
    public:
        void init();
        void update();
        void clear();
};

#endif