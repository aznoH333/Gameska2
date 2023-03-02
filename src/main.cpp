#include <raylib-cpp.hpp>
#include "gameObjects/entities/player/player.h"
#include "gameObjects/entities/enemies/enemy.h"
#include "gameObjects/world/world.h"
#include "sprites/SpriteManager.h"
#include "gameObjects/GameObjectManager.h"
#include "gameObjects/world/camera.h"
#include "gameObjects/entities/player/playerManager.h"

int main() {
    
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    raylib::Window w(screenWidth, screenHeight, "Gameska");
    
    GameObjectManager::getInstance()->addGameObject(new Player({40,40}));
    //GameObjectManager::getInstance()->addGameObject(new Enemy({100,40}));
    
    
    SetTargetFPS(60);
    while (!w.ShouldClose())
    {
        SpriteManager::getInstance()->beginDrawing();
        
        ClearBackground({40, 30, 30, 255});
        
        World::getInstance()->update();
        SpriteManager::getInstance()->update();
        GameObjectManager::getInstance()->update();
        CameraObject::getInstance()->update();
        PlayerManager::getInstance()->update();


        SpriteManager::getInstance()->endDrawing();
    }
    
    World::getInstance()->dispose();
    GameObjectManager::getInstance()->dispose();
    SpriteManager::getInstance()->dispose();
    CameraObject::getInstance()->dispose();
    PlayerManager::getInstance()->dispose();

    return 0;
}