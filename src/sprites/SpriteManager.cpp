#include "SpriteManager.h"
#include "raylib.h"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>

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

    // pick ups
    loadTexture("assets/entities/upgrade/Upgrade_box.png");
    loadTexture("assets/entities/upgrade/Grab_text.png");


    // fx
    loadTexture("assets/entities/fireFX/FireBallExplosion_1.png");
    loadTextures("assets/entities/fireFX/Muzzle_flash_", ".png", 1, 8);
    loadTextures("assets/entities/gore/Gore_", ".png", 1, 10);



    // ui
    loadTexture("assets/ui/Hud.png");
    loadTexture("assets/ui/Heart.png");
    loadTexture("assets/ui/Empty_Heart.png");
    loadTexture("assets/ui/menu_select.png");

    // logo
    loadTexture("assets/ui/Among.png");



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

    for (const auto& t : renderLayers){
        t.second->clear();
        delete t.second;
    }
    delete instance;
}

void SpriteManager::drawTexture(RenderData data){
    if (renderLayers.find(data.zIndex) == renderLayers.end()) 
        renderLayers.emplace(data.zIndex, new std::vector<RenderData>());

    renderLayers[data.zIndex]->push_back(data);
}


void SpriteManager::render(){

    beginDrawing();

    for (const auto& layer : renderLayers){
        for (RenderData data : *layer.second){
            renderTexture(data);
        }
        layer.second->clear();
    }
    
    endDrawing();
}

void SpriteManager::renderTexture(RenderData data){
    Texture2D texture = getTexture(data.texture);
    
    Vector2 calculatedWidth = {
        texture.width * data.scale, texture.height * data.scale
    };

    Vector2 origin = {0,0};
    
    Vector2 pos = data.pos;

    if (!data.isAbsolute){
        pos.x -= camerapos.x + shakeCameraAdder.x;
        pos.y -= camerapos.y + shakeCameraAdder.y;
        pos.x += (calculatedWidth.x / 2);
        pos.y += (calculatedWidth.y / 2);

    }else{
        // width offset
        pos.x -= (calculatedWidth.x / 2);
        pos.y -= (calculatedWidth.y / 2);
    }
    Color c = data.color;
    c.r *= currentColorFade;
    c.g *= currentColorFade;
    c.b *= currentColorFade;

    DrawTexturePro(texture, 
        {(data.flipSprite ? texture.width : 0.0f) ,0.0f, (data.flipSprite ? -texture.width + 0.1f : (float)texture.width), (float)texture.height}, 
        {pos.x, pos.y , calculatedWidth.x, calculatedWidth.y}, 
        {calculatedWidth.x / 2,calculatedWidth.y /2}, data.rotation, c);
}

void SpriteManager::update(){
    camerapos = world->getCameraPos();
    handleScreenShake();
}

void SpriteManager::beginDrawing(){
    BeginDrawing();
}

void SpriteManager::endDrawing(){
    EndDrawing();
}


float SpriteManager::getColorFade(){
    return currentColorFade;
}

void SpriteManager::setColorFade(float value){
    currentColorFade = value;
}

void SpriteManager::handleScreenShake(){
    

    if (screenShakeAmmount > 0){
        screenShakeTimer++;
        
        shakeCameraAdder.x = std::cos(screenShakeTimer) * screenShakeAmmount;
        shakeCameraAdder.y = std::sin(screenShakeTimer) * screenShakeAmmount;
        
        screenShakeAmmount -= screenShakeFallof;
        if (screenShakeAmmount < 0) {
            screenShakeAmmount = 0;
            shakeCameraAdder = {0,0};

        }
    }

}

void SpriteManager::addScreenShake(float ammount){
    screenShakeAmmount += ammount;
}


SpriteManager* SpriteManager::instance = 0;
