#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <map>
#include <string>
#include <raylib-cpp.hpp>
#include "../gameObjects/world/camera.h"
#include "raylib.h"
#include <vector>
#include <math.h>



enum DrawingLayers {
    layer_world = 0,
    layer_gore = 1,
    layer_pickups = 2,
    layer_enemy = 3,
    layer_projectiles = 4,
    layer_priority = 5,
    layer_hud = 6
};


struct RenderData{
    std::string texture;
    Vector2 pos;
    float scale = 2;
    float rotation = 0;
    raylib::Color color = WHITE;
    bool flipSprite = false;
    int zIndex = 0;
    bool isAbsolute = false;
};


class SpriteManager{
    private:
        static SpriteManager* instance;
        std::map<std::string, Texture2D> sprites;
        std::map<int, std::vector<RenderData>*> renderLayers;
        CameraObject* world;
        
        Vector2 camerapos;
        Vector2 shakeCameraAdder = {0,0};

        float currentColorFade = 0;


        // sreenshake stuff
        float screenShakeAmmount = 0;
        const float screenShakeFallof = 3;
        int screenShakeTimer = 0;
        

        SpriteManager();

        void renderTexture(RenderData data);
        void handleScreenShake();

    
    public:
        static SpriteManager* getInstance();
        void loadTexture(std::string);
        void loadTextures(std::string begin, std::string end, int beginN, int endN);
        Texture2D getTexture(std::string);
        void drawTexture(RenderData data);
        void render();
        void addScreenShake(float ammount);


        void dispose();
        void update();
        void beginDrawing();
        void endDrawing();

        float getColorFade();
        void setColorFade(float value);
};

#endif