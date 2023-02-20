#include "SpriteManager.h"
#include <string>
#include <iostream>

SpriteManager::SpriteManager(){
    loadTexture("assets/tiles/bricks.png");
    loadTexture("assets/tiles/missing.png");

    loadTextures("assets/entities/player/player_", ".png", 1, 9);
    loadTextures("assets/entities/basic_enemy/Enemy_", ".png", 1, 9);



    world = World::getInstance();
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
    for (int i = beginN; i < endN; i++){
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

void SpriteManager::drawTexture(std::string sprite, Vector2 pos, float scale, raylib::Color color){
    DrawTextureEx(getTexture(sprite), {pos.x - camerapos.x, pos.y - camerapos.y}, 0, scale, color);
}


void SpriteManager::update(){
    camerapos = world->getCameraPos();
}

SpriteManager* SpriteManager::instance = 0;
