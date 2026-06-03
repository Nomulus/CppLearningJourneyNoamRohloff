/*.\raylib\w64devkit\bin\g++.exe Pong.cpp -I.\raylib\raylib\src
 -L.\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm -o programm
 .\programm.exe*/

#include <iostream>
#include <raylib.h>

using namespace std;

int main() {
  cout << "Start Programming the game now";

  const int screen_width = 1200;
  const int screen_height = 800;
  InitWindow(GetScreenWidth(), screen_height, "PongByNoam");
  SetTargetFPS(60);
  while (WindowShouldClose() == false) {
    BeginDrawing();

    EndDrawing();
  }

  return 0;
}
