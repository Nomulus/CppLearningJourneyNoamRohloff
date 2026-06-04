/*.\raylib\w64devkit\bin\g++.exe Pong.cpp -I.\raylib\raylib\src
 -L.\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm -o programm
 .\programm.exe*/

#include <iostream>
#include <raylib.h>

using namespace std;

int main() {
  int deltaTime{};

  Vector2 WindowSize = {1200, 800};

  const int circleRadius = 20;
  Vector2 ballPos = {WindowSize.x / 2, WindowSize.y / 2};

  Vector2 startingPlayerSize = {20, 120};
  Vector2 player1Pos = {0, WindowSize.y / 2.0f - startingPlayerSize.y / 2};
  Vector2 player2Pos = {WindowSize.x - startingPlayerSize.x,
                        WindowSize.y / 2.0f - startingPlayerSize.y / 2};

  InitWindow(WindowSize.x, WindowSize.y, "PongByNoam");
  SetTargetFPS(144);

  while (WindowShouldClose() == false) {
    deltaTime = GetFrameTime();

    // ----------- updating ----------

    // ----------- drawing ---------------

    BeginDrawing();

    DrawCircleV(ballPos, circleRadius, WHITE);
    DrawRectangleV(player1Pos, startingPlayerSize, WHITE);
    DrawRectangleV(player2Pos, startingPlayerSize, WHITE);

    EndDrawing();
  }

  return 0;
}
