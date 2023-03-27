#include "animationObject.h"
#include "../../../sprites/SpriteManager.h"
#include <string>


AnimationObject::AnimationObject(Vector2 pos, std::string sprite, int animationStart, int animationEnd, int frameDuration, bool flipSprite) : GameObject(pos, {0, 0}, ObjectIdentifier::Other, 0){
    this->sprite = sprite;
    this->animationFrame = animationStart;
    this->animationEnd = animationEnd;
    this->frameDuration = frameDuration;
    this->flipSprite = flipSprite;
    currentFrameDuration = frameDuration;
}

AnimationObject::AnimationObject(Vector2 pos, std::string sprite, int animationStart, int animationEnd, int frameDuration, bool flipSprite, float rotation) : GameObject(pos, {0, 0}, ObjectIdentifier::Other, 0){
    this->sprite = sprite;
    this->animationFrame = animationStart;
    this->animationEnd = animationEnd;
    this->frameDuration = frameDuration;
    this->flipSprite = flipSprite;
    currentFrameDuration = frameDuration;
    this->rotation = rotation;
}

void AnimationObject::update(){

    SpriteManager::getInstance()->drawTexture({sprite + std::to_string(animationFrame), pos, 2, rotation, WHITE, flipSprite, layer_priority});

    currentFrameDuration--;
    if (currentFrameDuration == 0){

        animationFrame++;
        

        currentFrameDuration = frameDuration;
        if (animationFrame > animationEnd) destroy();

    }

}