#include "blood.h"
#include <cmath>
#include <string>
#include "../../GameObjectManager.h"

Blood::Blood(Vector2 pos, gore_type type): GameObject(pos, {16, 16}, Other, 1){
    z = GetRandomValue(1, 25);
    this->type = type;
    direction = GetRandomValue(0, 360) * DEG2RAD;

    
    if (type != type_droplet && type != type_blood_big){
        z_movement = GetRandomValue(6, 9);
        speed = GetRandomValue(15, 40) / 10.0f;
        rotate_left = GetRandomValue(0, 1) > 0;
        blood_sprite = GetRandomValue(1, 3);
    }else {
        z_movement = 0;
        speed = GetRandomValue(0, 10) / 10.0f;
        rotate_left = GetRandomValue(0, 1) > 0;
        blood_sprite = GetRandomValue(1, 3);
    }

    
    
    if (type == type_giblet){
        bounce_count = GetRandomValue(1, 2);
        sprite = "giblet_";
    }else{
        sprite = "blood_";
    }
}

void Blood::update(){
    if (is_airborne){
        SpriteManager::getInstance()->drawTexture({sprite + std::to_string(blood_sprite), {pos.x, pos.y - z}, 2, rotation, WHITE, rotate_left, layer_projectiles, false});
        

        if (rotate_left) rotation += 2;
        else rotation -= 2;
        
        pos.x += std::cos(direction) * speed;
        pos.y += std::sin(direction) * speed;

        z += z_movement;
        z_movement -= z_gravity;

        if (z <= 0){
            on_impact();
        } 

    }else {

        Color color = WHITE;
        color.a = ((float)despawn_time / (float)despawn_time_max) * 255;
        if (type != type_giblet)
            SpriteManager::getInstance()->drawTexture({sprite + std::to_string(blood_sprite), {pos.x - 8, pos.y - 8}, 2, rotation, color, rotate_left, layer_world, false});
        else
            SpriteManager::getInstance()->drawTexture({sprite + std::to_string(blood_sprite + 3), {pos.x, pos.y}, 2, 0, color, rotate_left, layer_pickups, false});

        
        despawn_time--;
        if (despawn_time == 0) destroy();        
    }
}

void Blood::on_impact(){
    bounce_count--;

    if (bounce_count <= 0){
        if (type == type_blood){
            blood_sprite = GetRandomValue(4, 8);
        }else if (type == type_blood_big){
            blood_sprite = GetRandomValue(1, 3);
            sprite = "blood_big_";
        }
        is_airborne = false;

    }
    else
        z_movement *= -1;
    
    if (type == type_giblet){
        for (int i = GetRandomValue(1, 3); i > 0; i--){
            GameObjectManager::getInstance()->addGameObject(new Blood(pos, type_blood));
        }
    }
}