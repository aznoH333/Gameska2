#ifndef SOUND_MANAGER
#define SOUND_MANAGER

#include <string>
#include <map>
#include "raylib.h"

class Sound_manager{
    private:
        Sound_manager();
        static Sound_manager* instance;
        std::map<std::string, Sound> sound_map;

        const int max_pitch_randomization = 15;

    public:
        static Sound_manager* get_instance();

        void load_sound(std::string path);
        void play_sound(std::string name);
        void play_sound(std::string name, float volume);

        void dispose();
};

#endif