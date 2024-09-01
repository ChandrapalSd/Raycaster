#pragma once
#include <raylib.h>


class Camera2D
{
private:
    Vector2 pos;
    Vector2 dir;
public:
    Camera2D();
    ~Camera2D();
};


