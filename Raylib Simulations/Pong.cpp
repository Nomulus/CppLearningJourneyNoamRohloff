/* g++ Pong.cpp -lraylib -o pong.exe*/

#include <iostream>
#include <random>
#include <raylib.h>
#include <raymath.h>

using namespace std;

float IncreaseSpeed(float speed, bool isPlayer) {
  if (isPlayer) {
    return speed + 20.0f;
  } else {
    return speed + 30.0f;
  }
}

int StandardLoop(Vector2 windowSize, int startingSide, int FPS) {
  const int ballRadius = 13;
  Vector2 ballPos = {windowSize.x / 2, windowSize.y / 2};
  Vector2 newBallPos = {};
  Vector2 ballSpeed{10000, 0};

  random_device rd;
  mt19937 gen(rd());

  uniform_int_distribution<int> distrX(600, 700);
  uniform_int_distribution<int> distrY(-300, 300);

  if (startingSide == 2) {
    ballSpeed = {-(float)distrX(gen), -(float)distrY(gen)};
    ballPos.x = windowSize.x - windowSize.x / 4;
  } else {
    ballSpeed = {(float)distrX(gen), (float)distrY(gen)};
    ballPos.x = windowSize.x / 4;
  }

  Vector2 player1Size{20, 120};
  Vector2 player2Size{20, 120};
  Vector2 player1Pos = {0, windowSize.y / 2.0f - player1Size.y / 2};
  Vector2 player2Pos = {windowSize.x - player2Size.x,
                        windowSize.y / 2.0f - player2Size.y / 2};

  int player1Speed = 400.0f;
  int player2Speed = 400.0f;

  double deltaTime{};

  while (WindowShouldClose() == false) {
    deltaTime = GetFrameTime();
    if (deltaTime > 1.0f / (float)FPS + 0.1f / (float)FPS) {
      cout << "deltaTime Warning: " << deltaTime << " ms" << endl;
    }

    // -------- player movement ----------
    player1MovingUp = false;
    player1MovingDown = false;
    player2MovingUp = false;
    player2MovingDown = false;

    if (IsKeyDown(KEY_W) && (player1Pos.y > 0)) {
      player1Pos.y -= player1Speed * GetFrameTime();
      player1MovingUp = true;
    }
    if (IsKeyDown(KEY_S) && (player1Pos.y < windowSize.y - player1Size.y)) {
      player1Pos.y += player1Speed * GetFrameTime();
      player1MovingDown = true;
    }

    if (IsKeyDown(KEY_UP) && (player2Pos.y > 0)) {
      player2Pos.y -= player2Speed * GetFrameTime();
      player2MovingUp = true;
    }
    if (IsKeyDown(KEY_DOWN) && (player2Pos.y < windowSize.y - player2Size.y)) {
      player2Pos.y += player2Speed * GetFrameTime();
      player2MovingDown = true;
    }

    // -------- BallMovement----------

    // to reset ball to previous state if it collides -> no clipping
    newBallPos = Vector2Add(ballPos, Vector2Scale(ballSpeed, (float)deltaTime));

    // -------player hit -----
    ballPath = newBallPos - ballPos;
    // ------ wall hit --------
    if (newBallPos.x <= 0 + ballRadius) {
      return 2;
    }
    if (newBallPos.x >= windowSize.x - ballRadius) {
      return 1;
    }
    if ((ballPos.y < 0 + ballRadius) && (ballSpeed.y <= 0)) {
      ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      newBallPos = ballPos;
    }
    if ((ballPos.y > windowSize.y - ballRadius) && (ballSpeed.y >= 0)) {
      ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      newBallPos = ballPos;
    }
    ballPos = newBallPos;
    // ----------- drawing ---------------

    BeginDrawing();

    ClearBackground(GRAY);
    DrawRectangle(0, 0, windowSize.x, windowSize.y, BLACK);

    DrawCircleV(ballPos, ballRadius, WHITE);
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
  int FPS = 144;
  InitWindow(windowSize.x, windowSize.y, "PongByNoam");
  SetTargetFPS(FPS);
  while (WindowShouldClose() == false) {
    startingSide = StandardLoop(windowSize, startingSide, FPS);
  }
  return 0;
}
