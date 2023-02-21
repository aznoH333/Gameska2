#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <map>
#include <string>
#include <raylib-cpp.hpp>
#include "../gameObjects/world/camera.h"

class SpriteManager{
    private:
        static SpriteManager* instance;
        std::map<std::string, Texture2D> sprites;
        CameraObject* world;
        Vector2 camerapos;
        SpriteManager();

    
    public:
        static SpriteManager* getInstance();
        void loadTexture(std::string);
        void loadTextures(std::string begin, std::string end, int beginN, int endN);
        Texture2D getTexture(std::string);
        void drawTexture(std::string, Vector2, float, raylib::Color, bool flipSprite);
        void dispose();
        void update();
        void beginDrawing();
        void endDrawing();
};

#endif