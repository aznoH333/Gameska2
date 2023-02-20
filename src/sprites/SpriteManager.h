#ifndef SPRITE_MANAGER
#define SPRITE_MANAGER

#include <map>
#include <string>
#include <raylib-cpp.hpp>

class SpriteManager{
    private:
        static SpriteManager* instance;
        std::map<std::string, Texture2D> sprites;
        SpriteManager();

    
    public:
        static SpriteManager* getInstance();
        void loadTexture(std::string);
        void loadTextures(std::string begin, std::string end, int beginN, int endN);
        Texture2D getTexture(std::string);
        void drawTexture(std::string, Vector2, float, raylib::Color);
        void dispose();
};

#endif