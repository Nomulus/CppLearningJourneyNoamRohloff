/* g++ Pong.cpp -lraylib -o pong.exe*/

#include <cmath>
#include <iostream>
#include <random>
#include <raylib.h>
#include <raymath.h>
#include <type_traits>

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

  Vector2 player1Size{200, 120};
  Vector2 player2Size{20, 120};
  Vector2 player1Pos = {10, windowSize.y / 2.0f - player1Size.y / 2};
  Vector2 player2Pos = {windowSize.x - player2Size.x - 10,
                        windowSize.y / 2.0f - player2Size.y / 2};

  int player1Speed = 400.0f;
  int player2Speed = 400.0f;

  double deltaTime{};

  bool ballBehindPlayer1Front{};
  bool ballMiddleUnderPlayer1TopLine{};
  bool ballMiddleOverPlayer1BottomLine{};
  bool ballOverPlayer1BottomLine{};
  bool ballUnderPlayer1TopLine{};
  bool ballGoingTowordsPlayer1{};

  bool player1IsHitOnTop{};
  bool player1IsHitOnSide{};
  bool player1IsHitOnBottom{};

  bool player1MovingUp{};
  bool player1MovingDown{};

  bool ballBehindPlayer2Front{};
  bool ballMiddleUnderPlayer2TopLine{};
  bool ballMiddleOverPlayer2BottomLine{};
  bool ballOverPlayer2BottomLine{};
  bool ballUnderPlayer2TopLine{};
  bool ballGoingTowordsPlayer2{};

  bool player2IsHitOnTop{};
  bool player2IsHitOnSide{};
  bool player2IsHitOnBottom{};

  bool player2MovingUp{};
  bool player2MovingDown{};

  while (WindowShouldClose() == false) {
    deltaTime = GetFrameTime();
    if (deltaTime > 1.0f / (float)FPS + 0.1f / (float)FPS) {
      cout << "deltaTime Warning: " << deltaTime << " ms" << endl;
    }

    // ----------- updating ----------

    newBallPos = Vector2Add(ballPos, Vector2Scale(ballSpeed, (float)deltaTime));

    // -------player 1 hit ----------

    // where is ball relative to player
    ballBehindPlayer1Front =
        (ballPos.x - ballRadius) <= (player1Pos.x + player1Size.x);

    ballMiddleUnderPlayer1TopLine = newBallPos.y >= player1Pos.y;

    ballMiddleOverPlayer1BottomLine =
        newBallPos.y <= player1Pos.y + player1Size.y;

    ballGoingTowordsPlayer1 = ballSpeed.x <= 0;

    ballUnderPlayer1TopLine = (ballPos.y + ballRadius) >= player1Pos.y;

    ballOverPlayer1BottomLine =
        (ballPos.y - ballRadius) <= player1Pos.y + player1Size.y;

    // did ball hit the Player
    player1IsHitOnSide =
        ((ballBehindPlayer1Front) && (ballMiddleUnderPlayer1TopLine) &&
         (ballMiddleOverPlayer1BottomLine) && (ballGoingTowordsPlayer1));

    player1IsHitOnTop =
        ((ballBehindPlayer1Front) && (ballUnderPlayer1TopLine) &&
         (ballGoingTowordsPlayer1));

    player1IsHitOnBottom =
        ((ballBehindPlayer1Front) && (ballOverPlayer1BottomLine) &&
         (ballGoingTowordsPlayer1));

    player1MovingUp = IsKeyDown(KEY_W) && (player1Pos.y > 0);
    player1MovingDown =
        IsKeyDown(KEY_S) && (player1Pos.y + player1Size.y < windowSize.y);

    if (player1IsHitOnSide) {
      player1Speed = IncreaseSpeed(player1Speed, true);
      ballSpeed.x = IncreaseSpeed(ballSpeed.x, false);
      newBallPos = ballPos;
      if (player1MovingUp) {
        ballSpeed.y = ballSpeed.y - 200;
      }
      if (player1MovingDown) {
        ballSpeed.y = ballSpeed.y + 200;
      }
      cout << "hit side " << endl;

    } else if (player1IsHitOnTop) {
      player1Speed = IncreaseSpeed(player1Speed, true);
      if (ballSpeed.y <= 0) {
        ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      } else {
        ballSpeed.y = IncreaseSpeed(ballSpeed.y, false);
      }
      ballPos.y = player1Pos.y - ballRadius;
      cout << "hit top " << endl;

    } else if (player1IsHitOnBottom) {
      player1Speed = IncreaseSpeed(player1Speed, true);
      if (ballSpeed.y >= 0) {
        ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      } else {
        ballSpeed.y = IncreaseSpeed(ballSpeed.y, false);
      }
      ballPos.y = player1Pos.y + ballRadius;
      cout << "hit bottom " << endl;
    }
    // -------player 2 hit ----------

    // where is ball relative to player
    ballBehindPlayer2Front = (ballPos.x + ballRadius) >= player2Pos.x;

    ballMiddleUnderPlayer2TopLine = newBallPos.y >= player2Pos.y;

    ballMiddleOverPlayer2BottomLine =
        newBallPos.y <= player2Pos.y + player2Size.y;

    ballGoingTowordsPlayer2 = ballSpeed.x >= 0;

    ballUnderPlayer2TopLine = (ballPos.y + ballRadius) >= player2Pos.y;

    ballOverPlayer2BottomLine =
        (ballPos.y - ballRadius) <= player2Pos.y + player2Size.y;

    // did ball hit the Player
    player2IsHitOnSide =
        ((ballBehindPlayer2Front) && (ballMiddleUnderPlayer2TopLine) &&
         (ballMiddleOverPlayer2BottomLine) && (ballGoingTowordsPlayer2));

    player2IsHitOnTop =
        ((ballBehindPlayer2Front) && (ballUnderPlayer2TopLine) &&
         (ballGoingTowordsPlayer2));

    player2IsHitOnBottom =
        ((ballBehindPlayer2Front) && (ballOverPlayer2BottomLine) &&
         (ballGoingTowordsPlayer2));

    player2MovingUp = IsKeyDown(KEY_W) && (player2Pos.y > 0);
    player2MovingDown =
        IsKeyDown(KEY_S) && (player2Pos.y + player2Size.y < windowSize.y);

    if (player2IsHitOnSide) {
      player2Speed = IncreaseSpeed(player2Speed, true);
      ballSpeed.x = -IncreaseSpeed(ballSpeed.x, false);
      newBallPos = ballPos;
      if (player2MovingUp) {
        ballSpeed.y = ballSpeed.y - 200;
      }
      if (player2MovingDown) {
        ballSpeed.y = ballSpeed.y + 200;
      }
    } else if (player2IsHitOnTop) {
      player2Speed = IncreaseSpeed(player2Speed, true);
      ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      ballPos.y = player2Pos.y - ballRadius;
    } else if (player2IsHitOnBottom) {
      player2Speed = IncreaseSpeed(player2Speed, true);
      ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      ballPos.y = player2Pos.y + ballRadius;
    }

    // ------ wall hit --------
    if (ballPos.x < 0 + ballRadius) {
      return 2;
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
