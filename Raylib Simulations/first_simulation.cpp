/*.\raylib\w64devkit\bin\g++.exe first_simulation.cpp -I.\raylib\raylib\src -L.\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm -o programm
 .\programm.exe*/
#include "raylib.h"
#include "raymath.h"
#include <vector>

struct Charge
{
    Vector2 position{};
    float value{};
};

const float K{5000.0};

Vector2 CalculateTotalField(Vector2 point, const std::vector<Charge> &charges)
{
    Vector2 totalField = {0.0f, 0.0f};

    for (const auto &charge : charges)
    {
        Vector2 r = Vector2Subtract(point, charge.position);
        float distance = Vector2Length(r);

        if (distance < 1.0f)
        {
            continue;
        }

        float fieldMagnitude = K * charge.value / (distance * distance);

        Vector2 direction = Vector2Normalize(r);

        Vector2 individualField = Vector2Scale(direction, fieldMagnitude);

        totalField = Vector2Add(totalField, individualField);
    }

    return totalField;
}

float CalculateTotalPotential(Vector2 point, const std::vector<Charge> &charges)
{
    float totalPotential{0.0};

    for (const auto &charge : charges)
    {

        Vector2 r = Vector2Subtract(point, charge.position);
        float distance = Vector2Length(r);

        if (distance < 1.0f)
        {
            continue;
        }

        float potential = K * charge.value / distance;

        totalPotential += potential;
    }
    return totalPotential;
}

int main()
{
    float ballX{400.0};
    float ballY{400.0};
    const float minPotential{100.0};
    const float maxPotential{1000.0};
    Color green = {20, 160, 133, 255};

    InitWindow(500, 500, "My First raylib Game");
    SetTargetFPS(60);
    std::vector<Charge> charges;

    charges.push_back({{ballX, ballY}, 10.0f});

    while (WindowShouldClose() == false)
    {
        for (int y{0}; y < GetScreenHeight(); y++)
        {
            for (int x{0}; x < GetScreenWidth(); x++)
            {
                Vector2 pixelPoint = {(float)x, (float)y};
                float potential = CalculateTotalPotential(pixelPoint, charges);

                float t = (potential - minPotential) / (maxPotential - minPotential);
                t = Clamp(t, 0.0f, 1.0f);

                Color pixelColor = {
                    (unsigned char)(t * 255),
                    (unsigned char)((1.0f - t) * 255),
                    (unsigned char)(150)};

                DrawPixel(x, y, pixelColor);
            }
        }
        if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
        {
            ballX -= 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        {
            ballX += 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
        {
            ballY -= 200 * GetFrameTime();
        }
        if (IsKeyDown(KEY_S) && !IsKeyDown(KEY_W))
        {
            ballY += 200 * GetFrameTime();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        charges[0].position = {ballX, ballY};
        DrawCircle(ballX, ballY, 20, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
