#ifndef GAME_STATE
#define GAME_STATE

#include <string>
#include <functional>

struct Button{
    std::string text = "placeholder";
    std::function<void()> function = [](){};
};


class GameState{
    public:
        virtual void update();
        virtual void clear();
        virtual void init();
};

#endif