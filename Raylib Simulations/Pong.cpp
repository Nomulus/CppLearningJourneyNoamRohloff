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

    // ----------- updating ----------

    newBallPos = Vector2Add(ballPos, Vector2Scale(ballSpeed, (float)deltaTime));

    // -------player 1 hit ----------
    if (((ballPos.x - ballRadius) <= (player1Pos.x + player1Size.x)) &&
        (ballPos.y >= player1Pos.y) &&
        (ballPos.y <= player1Pos.y + player1Size.y) && (ballSpeed.x <= 0)) {
      player1Speed = IncreaseSpeed(player1Speed, true);
      ballSpeed.x = -IncreaseSpeed(ballSpeed.x, false);
      newBallPos = ballPos;
      printf("hitPlayer1");
    }
    // -------player 2 hit ----------
    if ((ballPos.x + ballRadius >= player2Pos.x) &&
        (ballPos.y >= player2Pos.y) &&
        (ballPos.y <= player2Pos.y + player2Size.y) && (ballSpeed.x >= 0)) {
      player2Speed = IncreaseSpeed(player2Speed, true);
      ballSpeed.x = -IncreaseSpeed(ballSpeed.x, false);
      newBallPos = ballPos;
      printf("hitPlayer2");
    }
    // ------ wall hit --------
    if (ballPos.x < 0 + ballRadius) {
      return 1;
    }
    if (ballPos.x > windowSize.x - ballRadius) {
      return 2;
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

    // todo : adjust ballSpeed to speed hit by Player

    // -------- player movement ----------

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
