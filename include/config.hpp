#include <raylib.h>

namespace config
{
    const int TargetFPS = 60;
    const int WindowWidth = 702;
    const int WindowHeight = 702;
    const char* WindowTitle = "Raylib RayCaster";
    const Color bgColor = BLACK;

    const float fovDeg = 60;
    const float pointRadius = 5;
    const float cellPadding = 3;
    const int cellSize = 70;
    const int mapR = 10, mapC = 10;
    const int map[mapR][mapC] = 
    {
        {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    const Color mapColors[] = {WHITE, DARKGRAY};

}

