#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <map>
#include <string>
#include <raylib-cpp.hpp>
#include "../gameObjects/world/camera.h"
#include "raylib.h"
#include <vector>


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
        SpriteManager();

        void renderTexture(RenderData data);

    
    public:
        static SpriteManager* getInstance();
        void loadTexture(std::string);
        void loadTextures(std::string begin, std::string end, int beginN, int endN);
        Texture2D getTexture(std::string);
        void drawTexture(RenderData data);
        void render();


        void dispose();
        void update();
        void beginDrawing();
        void endDrawing();
};

#endif