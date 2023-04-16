#include "sound_manager.h"

#include <iostream>

Sound_manager* Sound_manager::get_instance(){
    if (!instance) instance = new Sound_manager();
    return instance;
}

Sound_manager* Sound_manager::instance = 0;

Sound_manager::Sound_manager(){
    // load sounds
    load_sound("assets/sounds/Roztylska_3.wav");
    load_sound("assets/sounds/sam_3.wav");

}

void Sound_manager::load_sound(std::string path){
    std::string name = path.substr(path.find_last_of("/")+1);
    name = name.substr(0, name.find_last_of("."));
    std::cout << "Loaded : " + name << std::endl;
    
    sound_map[name] = LoadSound(path.c_str());
}

void Sound_manager::play_sound(std::string name){
    PlaySound(sound_map[name]);
}


void Sound_manager::dispose(){
    delete instance;
}