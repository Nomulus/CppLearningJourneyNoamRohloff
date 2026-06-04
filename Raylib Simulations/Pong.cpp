/* g++ Pong.cpp -lraylib -o pong.exe*/

#include <iostream>
#include <raylib.h>

using namespace std;

int main() {
  float deltaTime{0.0f};

  Vector2 WindowSize = {1200, 800};

  const int circleRadius = 20;
  Vector2 ballPos = {WindowSize.x / 2, WindowSize.y / 2};

  Vector2 player1Size{20, 120};
  Vector2 player2Size{20, 120};
  Vector2 player1Pos = {0, WindowSize.y / 2.0f - player1Size.y / 2};
  Vector2 player2Pos = {WindowSize.x - player2Size.x,
                        WindowSize.y / 2.0f - player2Size.y / 2};

  int player1Speed = 3.0f;
  int player2Speed = 3.0f;

  InitWindow(WindowSize.x, WindowSize.y, "PongByNoam");
  SetTargetFPS(144);

  while (WindowShouldClose() == false) {
    deltaTime = GetFrameTime();

    // ----------- updating ----------

    if (IsKeyDown(KEY_W) && (player1Pos.y > 0)) {
      player1Pos.y -= player1Speed;
    }
    if (IsKeyDown(KEY_S) && (player1Pos.y < WindowSize.y - player1Size.y)) {
      player1Pos.y += player1Speed;
    }

    if (IsKeyDown(KEY_UP) && (player2Pos.y > 0)) {
      player2Pos.y -= player2Speed;
    }
    if (IsKeyDown(KEY_DOWN) && (player2Pos.y < WindowSize.y - player2Size.y)) {
      player2Pos.y += player2Speed;
    }
    // ----------- drawing ---------------
    BeginDrawing();

    ClearBackground(BLACK);

    DrawCircleV(ballPos, circleRadius, WHITE);
    DrawRectangleV(player1Pos, player1Size, WHITE);
    DrawRectangleV(player2Pos, player2Size, WHITE);

    EndDrawing();
  }

  return 0;
}
