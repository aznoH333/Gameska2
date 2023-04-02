#include <raylib-cpp.hpp>
#include "gamestates/Gamestate.h"
#include "raylib.h"
#include "gamestates/GameStateManager.h"
#include "sprites/SpriteManager.h"

int main() {
    
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;

    raylib::Window w(screenWidth, screenHeight, "Gameska");
    
    
    
    SetTargetFPS(60);
    ToggleFullscreen();

    SpriteManager::getInstance()->initCamera();
    GameStateManager* gameStateManager = GameStateManager::getInstance();
    while (!w.ShouldClose() && !gameStateManager->shouldGameEnd())
    {
        ClearBackground({0, 0, 0, 255});
        gameStateManager->update();
        
        SpriteManager::getInstance()->render();
    }
    
    gameStateManager->dispose();
    
    World::getInstance()->dispose();
    GameObjectManager::getInstance()->dispose();
    SpriteManager::getInstance()->dispose();
    CameraObject::getInstance()->dispose();
    PlayerManager::getInstance()->dispose();
    UIManager::getInstance()->dispose();




    return 0;
}