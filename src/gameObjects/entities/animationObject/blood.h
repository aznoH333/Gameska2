#ifndef BLOOD 
#define BLOOD

#include "../../GameObject.h"
#include "../../../sprites/SpriteManager.h"
#include "../../sound_manager.h"


enum gore_type{
    type_blood,
    type_giblet,
    type_droplet,
    type_blood_big
};


class Blood : public GameObject{
    private:
        float z;
        float z_movement;
        const float z_gravity = 2.0f;
        float direction;
        float rotation = 0;
        float speed;
        bool is_airborne = true;
        const int despawn_time_max = 600;
        int despawn_time = despawn_time_max;
        bool rotate_left;
        int blood_sprite;
        gore_type type;
        int bounce_count = 0;
        std::string sprite;


        void on_impact();

    
    public:
        Blood(Vector2 pos, gore_type type);
        void update();
        


};

#endif