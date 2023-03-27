#ifndef ANIMATION_OBJECT
#define ANIMATION_OBJECT

#include "../../GameObject.h"

class AnimationObject : public GameObject{
    
    private:
        std::string sprite;
        int animationFrame;
        int animationEnd;
        int frameDuration;
        int currentFrameDuration;
        bool flipSprite;
        float rotation = 0;
    
    
    
    public:
        AnimationObject(Vector2 pos, std::string sprite, int animationStart, int animationEnd, int frameDuration, bool flipSprite, float rotation);
        AnimationObject(Vector2 pos, std::string sprite, int animationStart, int animationEnd, int frameDuration, bool flipSprite);
        void update();
};

#endif