#pragma once
#include <raylib.h>

namespace cp
{
    

    class Camera2D
    {
    public:
        Vector2 pos{22, 12};
        Vector2 dir{-1, 0};
        Vector2 plane{0, 0.66}; // Perpendicular to dir
    public:
        Camera2D();
    };

} // namespace cp

