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
        void drawTexture(std::string sprite, Vector2 position, float scale, float rotation, raylib::Color color, bool flipSprite);

        void dispose();
        void update();
        void beginDrawing();
        void endDrawing();
};

#endif