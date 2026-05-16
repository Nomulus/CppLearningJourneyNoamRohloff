/*.\raylib\w64devkit\bin\g++.exe first_simulation.cpp -I.\raylib\raylib\src -L.\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm -o programm
 .\programm.exe*/
#include "raylib.h"
#include "raymath.h"

int main()
{
    int ballX{400};
    int ballY{400};
    Color green = {20, 160, 133, 255};

    InitWindow(800, 800, "My First raylib Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            ballX -= 3;
        }
        else if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            ballX += 3;
        }
        if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
        {
            ballY -= 3;
        }
        else if (IsKeyDown(KEY_S) && !IsKeyDown(KEY_W))
        {
            ballY += 3;
        }

        BeginDrawing();
        ClearBackground(green);
        DrawCircle(ballX, ballY, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
