#include "particles.h"
#include "raylib.h"

Bubble::Bubble(Vector2 pos): GameObject(pos, {16,16}, ObjectIdentifier::Other, 1){
    t = GetRandomValue(0, 20); // init random movement offset
    rotation = GetRandomValue(0, 359); // random rotation
    lifeTime = baseLifeTime + GetRandomValue(0, 20);
}

void Bubble::update(){
    t++;

    if (t < lifeTime){
        
        if (scale < 1) scale += 0.1;
        
        pos.y -= speed;
        pos.x += std::sin(t) * waveMultiplier;
        SpriteManager::getInstance()->drawTexture({"portal_particle_1", pos, scale * 2, rotation, WHITE, false, layer_priority});

    }else if (t < lifeTime + 20) {
        SpriteManager::getInstance()->drawTexture({"portal_particle_2", pos, scale * 2, rotation, WHITE, false, layer_priority});

    }else {
        destroy();
    }
    

}