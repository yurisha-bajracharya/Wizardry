#include "C:\raylib\raylib\src\raylib.h"
#include "Pause1.h"
#include <iostream>
#include "collectibles.h"
#include "string"
#include "button.h"
#include "globals.h"

Texture2D pause2bg;

void InitPause2()
{
    pause2bg = LoadTexture("./images/pause2bg.png");
}

void UnloadPause2()
{
    UnloadTexture(pause2bg);
}

void UpdatePause2()
{
}

void DrawPause2()
{
    DrawTexture(pause2bg, 0, 0, WHITE);
    DrawTextEx(fontNormal, (std::to_string(coinsCollected)).c_str(), (Vector2){380, 33}, 43, 2, BLACK);
    DrawTextEx(fontBold, (std::to_string(coinsCollected / 3)).c_str(), (Vector2){380, 83}, 50, 2, BLACK);
}
