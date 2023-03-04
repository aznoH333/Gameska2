#include "SpriteManager.h"
#include "raylib.h"
#include <string>
#include <iostream>

SpriteManager::SpriteManager(){
    loadTexture("assets/tiles/bricks.png");
    loadTexture("assets/tiles/missing.png");


    // player
    loadTextures("assets/entities/player/player_", ".png", 1, 9);
    
    // enemies
    loadTextures("assets/entities/basic_enemy/Enemy_", ".png", 1, 9);
    loadTextures("assets/entities/fire_enemy/Fire_Enemy_", ".png", 1, 9);


    loadTextures("assets/entities/drones/Amogus_", ".png",1, 6);

    loadTexture("assets/tiles/floor_tile.png");
    loadTexture("assets/tiles/brick_wall.png");
    // projectiles
    loadTexture("assets/entities/projectiles/bullet.png");
    loadTexture("assets/entities/projectiles/rocket.png");


    loadTexture("assets/entities/fireFX/Fire_ball.png");



    // fx
    loadTexture("assets/entities/fireFX/FireBallExplosion_1.png");
    loadTextures("assets/entities/fireFX/Muzzle_flash_", ".png", 1, 8);


    // hud
    loadTexture("assets/ui/Hud.png");
    loadTexture("assets/ui/Heart.png");
    loadTexture("assets/ui/Empty_Heart.png");


    world = CameraObject::getInstance();
}

SpriteManager* SpriteManager::getInstance(){
    if (!instance) instance = new SpriteManager();
    return instance;
}

Texture2D SpriteManager::getTexture(std::string name){
    return sprites[name];
}

void SpriteManager::loadTexture(std::string path){
    std::string name = path.substr(path.find_last_of("/")+1);
    name = name.substr(0, name.find_last_of("."));
    sprites[name] = LoadTexture(path.c_str());
}


void SpriteManager::loadTextures(std::string begin, std::string end, int beginN, int endN){
    for (int i = beginN; i <= endN; i++){
        loadTexture(begin + std::to_string(i) + end);
        std::cout << begin + std::to_string(i) + end + "\n";
    }
}

void SpriteManager::dispose(){
    for (const auto& t : sprites){
        UnloadTexture(t.second);
    }
    delete instance;
}

void SpriteManager::drawTexture(std::string sprite, Vector2 pos, float scale, float rotation, raylib::Color color, bool flipSprite){
    Texture2D texture = getTexture(sprite);
    //DrawTextureEx(getTexture(sprite), {pos.x - camerapos.x, pos.y - camerapos.y}, 0, scale, color);
    
    Vector2 calculatedWidth = {
        texture.width * scale, texture.height * scale
    };
    
    DrawTexturePro(texture, 
        {(flipSprite ? texture.width : 0.0f) ,0.0f, (flipSprite ? -texture.width + 0.1f : (float)texture.width), (float)texture.height}, 
        {pos.x - camerapos.x + (calculatedWidth.x / 2), pos.y - camerapos.y + (calculatedWidth.y / 2), calculatedWidth.x, calculatedWidth.y}, 
        {calculatedWidth.x / 2,calculatedWidth.y /2}, rotation, color);
}

void SpriteManager::drawTextureAbsolute(std::string sprite, Vector2 pos, float scale, float rotation, raylib::Color color, bool flipSprite){
    Texture2D texture = getTexture(sprite);
    //DrawTextureEx(getTexture(sprite), {pos.x - camerapos.x, pos.y - camerapos.y}, 0, scale, color);
    
    Vector2 calculatedWidth = {
        texture.width * scale, texture.height * scale
    };
    
    DrawTexturePro(texture, 
        {(flipSprite ? texture.width : 0.0f) ,0.0f, (flipSprite ? -texture.width + 0.1f : (float)texture.width), (float)texture.height}, 
        {pos.x - (calculatedWidth.x/2), pos.y - (calculatedWidth.y/2), calculatedWidth.x, calculatedWidth.y}, 
        {calculatedWidth.x / 2,calculatedWidth.y /2}, rotation, color);
}


void SpriteManager::update(){
    camerapos = world->getCameraPos();
}

void SpriteManager::beginDrawing(){
    BeginDrawing();
}

void SpriteManager::endDrawing(){
    EndDrawing();
}

SpriteManager* SpriteManager::instance = 0;
