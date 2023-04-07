#ifndef CameraObject_OBJECT
#define CameraObject_OBJECT

#include "raylib.h"
#include <raylib-cpp.hpp>



class CameraObject{
    private:
        Vector2 CameraObjectPos = {};
        Vector2 desiredCameraPos = {};
        static CameraObject* instance;
        const float cameraSpeed = 10.0f;


    public:
        void setCameraPos(Vector2 pos);
        void teleportCamera(Vector2 pos);
        Vector2 getCameraPos();
        void update();
        static CameraObject* getInstance();
        void dispose();
};

#endif