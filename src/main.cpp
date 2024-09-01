#include <raylib.h>
#include <iostream>
#include <vector>
#include <cassert>
#include "config.hpp"

float distSq(Vector2 a, Vector2 b)
{
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

Vector2 rayStep(const Vector2 s, const Vector2 e)
{
    int nextXOffset = (e.x > s.x) ? 1 : 0; 
    Vector2 nextX = s;
    nextX.x = ((int)s.x/config::cellSize + nextXOffset)*config::cellSize + (float)config::cellPadding/2;
    if(nextX.x == s.x)
        nextX.x = ((int)s.x/config::cellSize -1)*config::cellSize + (float)config::cellPadding/2;



    int nextYOffset = (e.y > s.y) ? 1 : 0; 
    Vector2 nextY = s;
    nextY.y = ((int)s.y/config::cellSize + nextYOffset)*config::cellSize + (float)config::cellPadding/2;
    if(nextY.y == s.y)
        nextY.y = ((int)s.y/config::cellSize -1)*config::cellSize + (float)config::cellPadding/2;

    // vertical line
    if(e.x == s.x)
    {
        return nextY;
    }
    // horizontal line
    else if(e.y == s.y)
    {
        return nextX;
    }

    float slope = (e.y-s.y)/(e.x-s.x);
    nextX.y = slope*(nextX.x-s.x) + s.y;
    nextY.x = (nextY.y-s.y)/slope + s.x;

    float dx = distSq(s, nextX);
    float dy = distSq(s, nextY);
    
    return dx<dy ? nextX : nextY;
}

Vector2 rayStep(const Vector2 s, const Vector2 e, int stepCount)
{
    Vector2 res = s;
    // assert(stepCount > 0 && "Step Count must be greater than or equal to 1");
    while (stepCount--)
    {
        res = rayStep(res, e);
    }
    return res;
}

std::vector<Vector2> raySteps(const Vector2 s, const Vector2 e, int stepCount)
{
    Vector2 res = s;
    std::vector<Vector2> resVec;
    resVec.reserve(stepCount);
    // assert(stepCount > 0 && "Step Count must be greater than or equal to 1");
    while (stepCount--)
    {
        res = rayStep(res, e);
        resVec.push_back(res);
    }
    return resVec;
}

int main()
{
    InitWindow(config::WindowWidth, config::WindowHeight, config::WindowTitle);
    SetTargetFPS(config::TargetFPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(config::bgColor);
        
        for (int i = 0; i < config::mapR; i++)
        {
            for (int j = 0; j < config::mapC; j++)
            {
                const Color c = config::mapColors[config::map[i][j]];
                DrawRectangle(i*config::cellSize +config::cellPadding, j*config::cellSize+config::cellPadding, config::cellSize-config::cellPadding, config::cellSize-config::cellPadding, c);
            }
        }
        
        const Vector2 s{321, 290};
        Vector2 e = GetMousePosition();
        // const Vector2 s{32, 20}, e{610, 400};
        // const Vector2 s{32, 470}, e{610, 0};
        // const Vector2 s{470, 570}, e{1, 11};
        // const Vector2 s{1, 11}, e{470, 570};

        // const Vector2 s{32, 32}, e{600, 32};
        // const Vector2 s{32, 32}, e{32, 600};
        float r = 7;
        float t = 3;
        DrawCircleV(s, r, RED);
        DrawLineEx(s, e, t, GREEN);

        float slope = (e.y-s.y)/(e.x-s.x);


        // DrawCircleV(nextX, r, BROWN);
        // std::cout << nextX.x << ", " << nextX.y << "  Slope: " << slope << std::endl;
        // DrawCircleV(nextY, r, PURPLE);
        
        
        std::vector<Vector2> results = raySteps(s, e, 20);
        for(const Vector2 res: results)
        {
            std::cout << res.x << ", " << res.y << std::endl;
            DrawCircleV(res, r/2, RED);
        }
        std::cout << "\n\n\n\n";
        
        // DrawCircleV(rayStep(s, e), r, ORANGE);
        // DrawCircleV(rayStep(s, e, 2), r, ORANGE);


        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}
