#include <raylib-cpp.hpp>
#include "gameObjects/entities/player/player.h"
#include "gameObjects/entities/enemies/enemy.h"
#include "sprites/SpriteManager.h"
#include "gameObjects/GameObjectManager.h"
#include "gameObjects/world/world.h"

int main() {
    
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    raylib::Window w(screenWidth, screenHeight, "Gameska");
    
    GameObjectManager::getInstance()->addGameObject(new Player({40,40}));
    GameObjectManager::getInstance()->addGameObject(new Enemy({100,40}));
    
    
    SetTargetFPS(60);
    while (!w.ShouldClose())
    {
        BeginDrawing();
        
        ClearBackground({40, 30, 30, 255});
        
        SpriteManager::getInstance()->update();
        GameObjectManager::getInstance()->update();
        
        EndDrawing();
    }
    
    GameObjectManager::getInstance()->dispose();
    SpriteManager::getInstance()->dispose();
    World::getInstance()->dispose();

    return 0;
}