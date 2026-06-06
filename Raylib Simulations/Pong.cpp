/* g++ Pong.cpp -lraylib -o pong.exe*/

#include <iostream>
#include <random>
#include <raylib.h>
#include <raymath.h>

using namespace std;

int StandardLoop(Vector2 windowSize, int startingSide) {

  const int circleRadius = 13;
  Vector2 ballPos = {windowSize.x / 2, windowSize.y / 2};
  Vector2 newBallPos = {};
  Vector2 ballSpeed{10000, 0};

  random_device rd;
  mt19937 gen(rd());

  uniform_int_distribution<int> distrX(600, 700);
  uniform_int_distribution<int> distrY(-300, 300);

  switch (startingSide) {
  case 2: {
    Vector2 ballSpeed = {(float)distrX(gen), -(float)distrY(gen)};
    break;
  }
  default: {
    Vector2 ballSpeed = {(float)distrX(gen), (float)distrY(gen)};
    break;
  }
  }

  Vector2 player1Size{20, 120};
  Vector2 player2Size{20, 120};
  Vector2 player1Pos = {0, windowSize.y / 2.0f - player1Size.y / 2};
  Vector2 player2Pos = {windowSize.x - player2Size.x,
                        windowSize.y / 2.0f - player2Size.y / 2};

  int player1Speed = 400.0f;
  int player2Speed = 400.0f;

  SetTargetFPS(144);
  double deltaTime{};

  while (WindowShouldClose() == false) {
    deltaTime = GetFrameTime();

    // ----------- updating ----------

    newBallPos = Vector2Add(ballPos, Vector2Scale(ballSpeed, (float)deltaTime));
    if (newBallPos.x < 0 + circleRadius) {
      ballSpeed.x = -ballSpeed.x - 100;
      newBallPos = ballPos;
    }
    if (newBallPos.x > windowSize.x - circleRadius) {
      ballSpeed.x = -ballSpeed.x - 100;
      newBallPos = ballPos;
    }
    if (newBallPos.y < 0 + circleRadius) {
      ballSpeed.y = -ballSpeed.y - 100;
      newBallPos = ballPos;
    }
    if (newBallPos.y > windowSize.y - circleRadius) {
      ballSpeed.y = -ballSpeed.y - 1.0;
      newBallPos = ballPos;
    }
    ballPos = newBallPos;

    // adjust ballSpeed to speed hit by Player
    //
    if (IsKeyDown(KEY_W) && (player1Pos.y > 0)) {
      player1Pos.y -= player1Speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S) && (player1Pos.y < windowSize.y - player1Size.y)) {
      player1Pos.y += player1Speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_UP) && (player2Pos.y > 0)) {
      player2Pos.y -= player2Speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN) && (player2Pos.y < windowSize.y - player2Size.y)) {
      player2Pos.y += player2Speed * GetFrameTime();
    }
    // ----------- drawing ---------------
    BeginDrawing();

    ClearBackground(GRAY);
    DrawRectangle(0, 0, windowSize.x, windowSize.y, BLACK);

    DrawCircleV(ballPos, circleRadius, WHITE);
    DrawRectangleV(player1Pos, player1Size, WHITE);
    DrawRectangleV(player2Pos, player2Size, WHITE);

    EndDrawing();
  }

  return 0;
}

int main() {
  float deltaTime{0.0f};

  Vector2 windowSize = {1280, 720};
  int startingSide{1};
  InitWindow(windowSize.x, windowSize.y, "PongByNoam");
  while (WindowShouldClose() == false) {
    startingSide = StandardLoop(windowSize, startingSide);
  }
  return 0;
}
