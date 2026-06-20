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

typedef enum GameScreen { TITLE, GAMEPLAY, BREAK } GameScreen;

int StandardLoop(Vector2 windowSize, int startingSide, int FPS) {
  Vector2 virtualSize = {720, 720};
  const int ballRadius = 13;
  Vector2 ballPos = {(float)virtualSize.x / 2, (float)virtualSize.y / 2};
  Vector2 newBallPos = ballPos;
  Vector2 ballSpeed{10000, 0};

  random_device rd;
  mt19937 gen(rd());

  uniform_int_distribution<int> distrX(400, 500);
  uniform_int_distribution<int> distrY(-200, 200);

  if (startingSide == 2) {
    ballSpeed = {-(float)distrX(gen), -(float)distrY(gen)};
    ballPos.x = virtualSize.x - virtualSize.x / 4;
  } else {
    ballSpeed = {(float)distrX(gen), (float)distrY(gen)};
    ballPos.x = virtualSize.x / 4;
  }

  Vector2 player1Size{20, 120};
  Vector2 player2Size{20, 120};
  Vector2 player1Pos = {10, virtualSize.y / 2.0f - player1Size.y / 2};
  Vector2 player2Pos = {virtualSize.x - player2Size.x - 10,
                        virtualSize.y / 2.0f - player2Size.y / 2};

  int player1Speed = 400.0f;
  int player2Speed = 400.0f;

  double deltaTime{};

  bool ballFrontBehindPlayer1Front{};
  bool ballMiddleUnderPlayer1TopLine{};
  bool ballMiddleOverPlayer1BottomLine{};
  bool ballOverPlayer1BottomLine{};
  bool ballUnderPlayer1TopLine{};
  bool ballGoingTowordsPlayer1{};
  bool ballMiddleBehindPlayer1Front{};

  bool player1IsHitOnTop{};
  bool player1IsHitOnSide{};
  bool player1IsHitOnBottom{};

  bool player1MovingUp{};
  bool player1MovingDown{};

  bool ballFrontBehindPlayer2Front{};
  bool ballMiddleUnderPlayer2TopLine{};
  bool ballMiddleOverPlayer2BottomLine{};
  bool ballOverPlayer2BottomLine{};
  bool ballUnderPlayer2TopLine{};
  bool ballGoingTowordsPlayer2{};
  bool ballMiddleBehindPlayer2Front{};

  bool player2IsHitOnTop{};
  bool player2IsHitOnSide{};
  bool player2IsHitOnBottom{};

  bool player2MovingUp{};
  bool player2MovingDown{};

  RenderTexture2D target = LoadRenderTexture(virtualSize.x, virtualSize.y);

  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

  while (WindowShouldClose() == false) {
    deltaTime = GetFrameTime();
    if (deltaTime > 1.0f / (float)FPS + 0.1f / (float)FPS) {
      cout << "deltaTime Warning: " << deltaTime << " ms" << endl;
    }

    // ----------- updating ----------

    newBallPos = ballPos + (ballSpeed * deltaTime);
    // -------- player movement ----------

    if (IsKeyDown(KEY_W) && (player1Pos.y > 0)) {
      player1Pos.y -= player1Speed * GetFrameTime();
      player1MovingUp = true;
    } else {
      player1MovingUp = false;
    }
    if (IsKeyDown(KEY_S) && (player1Pos.y < virtualSize.y - player1Size.y)) {
      player1Pos.y += player1Speed * GetFrameTime();
      player1MovingDown = true;
    } else {
      player1MovingDown = false;
    }

    if (IsKeyDown(KEY_UP) && (player2Pos.y > 0)) {
      player2Pos.y -= player2Speed * GetFrameTime();
      player2MovingUp = true;
    } else {
      player2MovingUp = false;
    }
    if (IsKeyDown(KEY_DOWN) && (player2Pos.y < virtualSize.y - player2Size.y)) {
      player2Pos.y += player2Speed * GetFrameTime();
      player2MovingDown = true;
    } else {
      player2MovingDown = false;
    }

    // -------player 1 hit ----------

    // where is ball relative to player
    ballFrontBehindPlayer1Front =
        (newBallPos.x - ballRadius) <= (player1Pos.x + player1Size.x);

    ballMiddleBehindPlayer1Front =
        (newBallPos.x) <= player1Pos.x + player1Size.x;

    ballMiddleUnderPlayer1TopLine =
        (newBallPos.y >= player1Pos.y) && ballFrontBehindPlayer1Front;

    ballMiddleOverPlayer1BottomLine =
        newBallPos.y <= (player1Pos.y + player1Size.y) &&
        ballFrontBehindPlayer1Front;

    ballGoingTowordsPlayer1 = (ballSpeed.x <= 0) && ballFrontBehindPlayer1Front;

    ballUnderPlayer1TopLine = ((ballPos.y + ballRadius) >= player1Pos.y) &&
                              ballFrontBehindPlayer1Front;

    ballOverPlayer1BottomLine =
        (ballPos.y - ballRadius) <= (player1Pos.y + player1Size.y) &&
        ballFrontBehindPlayer1Front;

    // did ball hit the Player
    player1IsHitOnSide =
        ((ballFrontBehindPlayer1Front) && (ballMiddleUnderPlayer1TopLine) &&
         (ballMiddleOverPlayer1BottomLine) && (ballGoingTowordsPlayer1) &&
         (ballPos.x > player1Pos.x + player1Size.x));

    player1IsHitOnTop =
        ((ballMiddleBehindPlayer1Front) && (ballUnderPlayer1TopLine) &&
         (ballOverPlayer1BottomLine) && (ballGoingTowordsPlayer1) &&
         (ballPos.y < player1Pos.y + 10));

    player1IsHitOnBottom =
        ((ballMiddleBehindPlayer1Front) && (ballOverPlayer1BottomLine) &&
         (ballUnderPlayer1TopLine) && (ballGoingTowordsPlayer1));

    if (player1IsHitOnSide) {
      player1Speed = IncreaseSpeed(player1Speed, true);
      ballSpeed.x = -IncreaseSpeed(ballSpeed.x, false);
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
        ballSpeed.y = IncreaseSpeed(ballSpeed.y, false);
      } else {
        ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      }
      newBallPos.y = player1Pos.y - ballRadius - 1;
      newBallPos.x = deltaTime * ballSpeed.x + ballPos.x;
      cout << "hit top " << endl;

    } else if (player1IsHitOnBottom) {
      player1Speed = IncreaseSpeed(player1Speed, true);
      if (ballSpeed.y >= 0) {
        ballSpeed.y = IncreaseSpeed(ballSpeed.y, false);
      } else {
        ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      }
      newBallPos.y = player1Pos.y + player1Size.y + ballRadius + 1;
      newBallPos.x = deltaTime * ballSpeed.x + ballPos.x;
      cout << "hit bottom " << endl;
    }
    // -------player 2 hit ----------

    // where is ball relative to player
    ballFrontBehindPlayer2Front = (newBallPos.x + ballRadius) >= (player2Pos.x);

    ballMiddleBehindPlayer2Front = (newBallPos.x) >= player2Pos.x;

    ballMiddleUnderPlayer2TopLine =
        (newBallPos.y >= player2Pos.y) && ballFrontBehindPlayer2Front;

    ballMiddleOverPlayer2BottomLine =
        newBallPos.y <= (player2Pos.y + player2Size.y) &&
        ballFrontBehindPlayer2Front;

    ballGoingTowordsPlayer2 = (ballSpeed.x >= 0) && ballFrontBehindPlayer2Front;

    ballUnderPlayer2TopLine = ((ballPos.y + ballRadius) >= player2Pos.y) &&
                              ballFrontBehindPlayer2Front;

    ballOverPlayer2BottomLine =
        (ballPos.y - ballRadius) <= (player2Pos.y + player2Size.y) &&
        ballFrontBehindPlayer2Front;

    // did ball hit the Player
    player2IsHitOnSide =
        ((ballFrontBehindPlayer2Front) && (ballMiddleUnderPlayer2TopLine) &&
         (ballMiddleOverPlayer2BottomLine) && (ballGoingTowordsPlayer2) &&
         (ballPos.x < player2Pos.x));

    player2IsHitOnTop =
        ((ballMiddleBehindPlayer2Front) && (ballUnderPlayer2TopLine) &&
         (ballOverPlayer2BottomLine) && (ballGoingTowordsPlayer2) &&
         (ballPos.y + ballRadius + 40 >= player2Pos.y));

    player2IsHitOnBottom =
        ((ballMiddleBehindPlayer2Front) && (ballOverPlayer2BottomLine) &&
         (ballUnderPlayer2TopLine) && (ballGoingTowordsPlayer2));

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
      cout << "hit side " << endl;

    } else if (player2IsHitOnTop) {
      player2Speed = IncreaseSpeed(player2Speed, true);
      if (ballSpeed.y <= 0) {
        ballSpeed.y = IncreaseSpeed(ballSpeed.y, false);
      } else {
        ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      }
      newBallPos.y = player2Pos.y - ballRadius - 2;
      cout << "hit top " << endl;

    } else if (player2IsHitOnBottom) {
      player2Speed = IncreaseSpeed(player2Speed, true);
      if (ballSpeed.y >= 0) {
        ballSpeed.y = IncreaseSpeed(ballSpeed.y, false);
      } else {
        ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      }
      newBallPos.y = player2Pos.y + player2Size.y + ballRadius + 2;
      cout << "hit bottom " << endl;
    }
    // ------ wall hit --------
    if (ballPos.x < 0 + ballRadius) {
      return 2;
    }
    if (ballPos.x > virtualSize.x - ballRadius) {
      return 2;
    }
    if ((ballPos.y < 0 + ballRadius) && (ballSpeed.y <= 0)) {
      ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      newBallPos = ballPos;
    }
    if ((ballPos.y > virtualSize.y - ballRadius) && (ballSpeed.y >= 0)) {
      ballSpeed.y = -IncreaseSpeed(ballSpeed.y, false);
      newBallPos = ballPos;
    }
    ballPos = newBallPos;

    // ----------- drawing ---------------
    BeginTextureMode(target);
    ClearBackground(DARKGREEN);
    DrawCircleV(ballPos, ballRadius, WHITE);
    DrawRectangleV(player1Pos, player1Size, WHITE);
    DrawRectangleV(player2Pos, player2Size, WHITE);
    EndTextureMode();

    BeginDrawing();

    // berechnung wie gross die texture2D angezeigt werden soll:
    float scale = min((float)GetScreenWidth() / (float)virtualSize.x,
                      (float)GetScreenHeight() / (float)virtualSize.y);
    ClearBackground(DARKGRAY);
    DrawRectangle(0, 0, virtualSize.x, virtualSize.y, BLACK);
    Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width,
                           -(float)target.texture.height};
    Rectangle destRec = {
        ((float)GetScreenWidth() - ((float)virtualSize.x) * scale) * 0.5f,
        ((float)GetScreenHeight() - ((float)virtualSize.y) * scale) * 0.5f,
        (float)virtualSize.x * scale, (float)virtualSize.y * scale};

    DrawTexturePro(target.texture, sourceRec, destRec, Vector2{0, 0}, 0.0f,
                   WHITE);
    EndDrawing();
  }
  UnloadRenderTexture(target);

  return 0;
}

int main() {
  Vector2 windowSize = {720, 720};
  int startingSide{1};
  int loser{0};
  int FPS = 60;
  InitWindow(windowSize.x, windowSize.y, "PongByNoam");

  GameScreen currentScreen = TITLE;
  SetTargetFPS(FPS);
  while (WindowShouldClose() == false) {

    ClearBackground(RAYWHITE);

    switch (currentScreen) {
    case TITLE: {
      if (IsKeyPressed(KEY_ENTER) || (IsGestureDetected(GESTURE_TAP))) {
        currentScreen = GAMEPLAY;
      }
      BeginDrawing();

      DrawRectangle(0, 0, windowSize.x, windowSize.y, GREEN);
      DrawText("Pong by Noam", 20, 20, 40, DARKGREEN);
      DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20,
               DARKGREEN);
      EndDrawing();
    } break;
    case GAMEPLAY: {
      loser = StandardLoop(windowSize, startingSide, FPS);
      if (loser) {
        currentScreen = BREAK;
      }
    } break;
    case BREAK: {
      if (IsKeyPressed(KEY_ENTER) || (IsGestureDetected(GESTURE_TAP))) {
        currentScreen = GAMEPLAY;
      }
      BeginDrawing();

      DrawRectangle(0, 0, windowSize.x, windowSize.y, GREEN);
      DrawText("Someone Lost, don't know who tho.", 20, 20, 40, DARKGREEN);
      DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20,
               DARKGREEN);
      EndDrawing();

      break;
    }
      return 0;
    }
  }
}
