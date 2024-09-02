#include <raylib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "config.hpp"
#include "camera.hpp"

void cpDrawPoint(const Vector2 pos, const float radius, const Color color)
{
    DrawCircleV(pos, radius, color);
    char txt[100];
    /*sprintf(txt, "%f, %f", pos.x, pos.y);
    DrawText(txt, pos.x, pos.y, 20, RED);*/
    /*sprintf(txt, "%d, %d", (int)std::floorf(pos.x / config::cellSize), (int)std::floorf(pos.y / config::cellSize));
    DrawText(txt, pos.x, pos.y, 20, RED);*/
}

float distSq(Vector2 a, Vector2 b)
{
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
        os << v.x << ", " << v.y;
        return os;
}

Vector2 rayStep(const Vector2 pos, const Vector2 dir)
{
    Vector2 nextX = pos, nextY = pos;
    int nextXOffset = (dir.x > 0) ? 1 : 0; 

    nextX.x = (std::floor(pos.x/config::cellSize) + nextXOffset)*config::cellSize;
    if (pos.x >= nextX.x && pos.x <= nextX.x + config::cellPadding)
        nextX.x = (std::floor(pos.x / config::cellSize) - 1) * config::cellSize;
    nextX.x += config::cellPadding / 2;


    int nextYOffset = (dir.y > 0) ? 1 : 0; 

    nextY.y = (std::floor(pos.y/config::cellSize) + nextYOffset)*config::cellSize;
    if (pos.y >= nextY.y && pos.y <= nextY.y + config::cellPadding)
        nextY.y = (std::floor(pos.y / config::cellSize) - 1) * config::cellSize;
    nextY.y += config::cellPadding / 2;

    // vertical line
    if(dir.x == 0)
    {
        return nextY;
    }
    // horizontal line
    else if(dir.y == 0)
    {
        return nextX;
    }

    float slope = dir.y/dir.x;
    nextX.y = (nextX.x-pos.x)*slope + pos.y;
    nextY.x = (nextY.y-pos.y)/slope + pos.x;
    
    float dx = distSq(pos, nextX);
    float dy = distSq(pos, nextY);
    
    return dx<dy ? nextX : nextY;
}

Vector2 rayStep(const Vector2 pos, const Vector2 dir, int stepCount)
{
    Vector2 res = pos;
    // assert(stepCount > 0 && "Step Count must be greater than or equal to 1");
    while (stepCount--)
    {
        res = rayStep(res, dir);
    }
    return res;
}

std::vector<Vector2> raySteps(const Vector2 pos, const Vector2 dir, int stepCount)
{
    Vector2 res = pos;
    std::vector<Vector2> resVec;
    resVec.reserve(stepCount);
    // assert(stepCount > 0 && "Step Count must be greater than or equal to 1");
    while (stepCount--)
    {
        res = rayStep(res, dir);
        resVec.push_back(res);
    }
    return resVec;
}

Vector2 castRay(const Vector2 pos, const Vector2 dir, const int map[][config::mapC], const int mapR , const int mapC, int r=7)
{
    Vector2 next = pos;

    while (next.y < config::WindowHeight && next.y > config::cellSize && next.x < config::WindowWidth && next.x > config::cellSize)
    {
        int x, y;
        if (dir.x < 0) 
            x = std::floorf((next.x - config::cellPadding) / config::cellSize);
        else
            x = std::floorf(next.x / config::cellSize);

        if (dir.y < 0)
            y = std::floorf((next.y - config::cellPadding) / config::cellSize);
        else
            y = std::floorf(next.y / config::cellSize);
        if(x>=mapR || x<0 || y<0 || y >=mapC || map[y][x]) 
            break;
        next = rayStep(next, dir);
        cpDrawPoint(next, r, PURPLE);
        // DrawCircleV(next, 7, PURPLE);
    }
    return next;
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
                DrawRectangle(j*config::cellSize +config::cellPadding, i*config::cellSize+config::cellPadding, config::cellSize-config::cellPadding, config::cellSize-config::cellPadding, c);
            }
        }
        
        
        const Vector2 s{config::cellSize*config::mapC/2, config::cellSize * config::mapR / 2 };
        Vector2 e = GetMousePosition();
        // const Vector2 s{32, 20}, e{610, 400};
        // const Vector2 s{32, 470}, e{610, 0};
        // const Vector2 s{470, 570}, e{1, 11};
        // const Vector2 s{1, 11}, e{470, 570};

        // const Vector2 s{32, 32}, e{600, 32};
        // const Vector2 s{32, 32}, e{32, 600};

        //const Vector2 s{ 241.5, 240 }, e{-1, -1};
        //e.x = 55;
        //e.y = 538;

        float r = config::pointRadius;
        float t = 3;
        Vector2 dir{e.x-s.x, e.y-s.y};
        DrawCircleV(s, r, RED);
        // DrawLineEx(s, e, t, GREEN);        
        
        /*std::vector<Vector2> results = raySteps(s, dir, 20);
        for(const Vector2 res: results)
        {
            DrawCircleV(res, r/2, RED);
        }*/
        
        Vector2 res = castRay(s, dir, config::map, config::mapR, config::mapC, r);
        //const Vector2 res = rayStep(s, dir);
        DrawLineEx(s, res, t, GREEN);        
        DrawCircleV(res, r/1.5, DARKPURPLE);

        /*char txt[100];
        sprintf(txt, "%f, %f", e.x, e.y);
        DrawText(txt, e.x+20, e.y, 20, DARKGREEN);*/

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}
