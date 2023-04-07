#include "camera.h"
#include <cmath>

CameraObject* CameraObject::getInstance(){
    if (!instance) instance = new CameraObject();
    return instance;
}


void CameraObject::dispose(){
    delete instance;
}

void CameraObject::setCameraPos(Vector2 pos){
    desiredCameraPos = pos;
}

Vector2 CameraObject::getCameraPos(){
    return CameraObjectPos;
}

void CameraObject::update(){
    if (std::abs(CameraObjectPos.x - desiredCameraPos.x) < cameraSpeed) CameraObjectPos.x = desiredCameraPos.x;
    else CameraObjectPos.x += std::copysign(cameraSpeed, desiredCameraPos.x - CameraObjectPos.x);
    
    if (std::abs(CameraObjectPos.y - desiredCameraPos.y) < cameraSpeed) CameraObjectPos.y = desiredCameraPos.y;
    else CameraObjectPos.y += std::copysign(cameraSpeed, desiredCameraPos.y - CameraObjectPos.y);
    
}

void CameraObject::teleportCamera(Vector2 pos){
    desiredCameraPos = pos;
    CameraObjectPos = pos;
}

CameraObject* CameraObject::instance = 0;