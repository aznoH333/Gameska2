#include <raylib-cpp.hpp>
#include "raylib.h"
#include "gamestates/GameStateManager.h"

int main() {
    
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    raylib::Window w(screenWidth, screenHeight, "Gameska");
    
    
    
    SetTargetFPS(60);
    ToggleFullscreen();

    GameStateManager* gameStateManager = GameStateManager::getInstance();
    while (!w.ShouldClose() && !gameStateManager->shouldGameEnd())
    {
        ClearBackground({0, 0, 0, 255});
        gameStateManager->update();
        
        SpriteManager::getInstance()->render();
    }
    
    World::getInstance()->dispose();
    GameObjectManager::getInstance()->dispose();
    SpriteManager::getInstance()->dispose();
    CameraObject::getInstance()->dispose();
    PlayerManager::getInstance()->dispose();
    gameStateManager->dispose();
    delete gameStateManager;


    return 0;
}