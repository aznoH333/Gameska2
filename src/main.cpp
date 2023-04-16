#include <raylib-cpp.hpp>
#include "gamestates/Gamestate.h"
#include "raylib.h"
#include "gamestates/GameStateManager.h"
#include "sprites/SpriteManager.h"
#include "gameObjects/sound_manager.h"
#include "gameObjects/Settings_Manager.h"

int main() {
    
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;
    

    

    raylib::Window w(GetMonitorWidth(0), GetMonitorHeight(0), "Gameska");
    Persistent_Data_Manager::get_instance()->init();

    //SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorWidth(GetCurrentMonitor()));
    ToggleFullscreen();
    InitAudioDevice();
    
    Image window_icon = LoadImage("assets/ui/menu_select.png");
    SetWindowIcon(window_icon);
    
    
    
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    SpriteManager::getInstance()->initCamera();
    GameStateManager* gameStateManager = GameStateManager::getInstance();
    while (!w.ShouldClose() && !gameStateManager->shouldGameEnd())
    {
        ClearBackground({0, 0, 0, 255});
        gameStateManager->update();
        
        SpriteManager::getInstance()->render();
    }
    
    gameStateManager->dispose();
    Persistent_Data_Manager::get_instance()->dispose();
    World::getInstance()->dispose();
    GameObjectManager::getInstance()->dispose();
    SpriteManager::getInstance()->dispose();
    CameraObject::getInstance()->dispose();
    PlayerManager::getInstance()->dispose();
    UIManager::getInstance()->dispose();
    Sound_manager::get_instance()->dispose();
    CloseAudioDevice();


    return 0;
    
}