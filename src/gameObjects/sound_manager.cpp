#include "sound_manager.h"
#include "raylib.h"

#include <iostream>

Sound_manager* Sound_manager::get_instance(){
    if (!instance) instance = new Sound_manager();
    return instance;
}

Sound_manager* Sound_manager::instance = 0;

Sound_manager::Sound_manager(){
    // load sounds
    load_sound("assets/sounds/intro_sound.wav");
    load_sound("assets/sounds/click.ogg");
    load_sound("assets/sounds/gun.ogg");
    load_sound("assets/sounds/explosion.ogg");
    load_sound("assets/sounds/gun.ogg");
    load_sound("assets/sounds/enemy_hit.ogg");
    load_sound("assets/sounds/enemy_death.ogg");
    load_sound("assets/sounds/enemy_fire.ogg");
    load_sound("assets/sounds/laser.ogg");
    load_sound("assets/sounds/pickup.ogg");
    load_sound("assets/sounds/rocket.ogg");
    load_sound("assets/sounds/shotgun.ogg");
    load_sound("assets/sounds/blood_splat.ogg");







}

void Sound_manager::load_sound(std::string path){
    std::string name = path.substr(path.find_last_of("/")+1);
    name = name.substr(0, name.find_last_of("."));
    std::cout << "Loaded : " + name << std::endl;
    
    sound_map[name] = LoadSound(path.c_str());
}

void Sound_manager::play_sound(std::string name){
    play_sound(name, 1);
}

void Sound_manager::play_sound(std::string name, float volume){
    SetSoundVolume(sound_map[name], volume);
    SetSoundPitch(sound_map[name], 1 + (GetRandomValue(-max_pitch_randomization, max_pitch_randomization) / 100.0f));
    PlaySound(sound_map[name]);
}


void Sound_manager::dispose(){
    delete instance;
}