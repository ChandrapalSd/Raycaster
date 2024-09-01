#include <raylib.h>

namespace config
{
    const int TargetFPS = 60;
    const int WindowWidth = 602;
    const int WindowHeight = 602;
    const char* WindowTitle = "Raylib RayCaster";
    const Color bgColor = BLACK;

    const int cellPadding = 3;
    const int cellSize = 60;
    const int mapR = 10, mapC = 10;
    const int map[mapR][mapC] = 
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    const Color mapColors[] = {WHITE, DARKGRAY};

}

