#include "C:\raylib\raylib\src\raylib.h"
#include "Pause1.h"
#include <iostream>
#include "collectibles.h"
#include "string"
#include "button.h"
#include "globals.h"

Texture2D pause1bg;

void InitPause1()
{
    pause1bg = LoadTexture("./images/pause1bg.png");
}

void UnloadPause1()
{
    UnloadTexture(pause1bg);
}

void UpdatePause1()
{
}

void DrawPause1()
{
    DrawTexture(pause1bg, 0, 0, WHITE);
    DrawTextEx(fontNormal, (std::to_string(CollectibleCount)).c_str(), (Vector2){390, 36}, 43, 2, BLACK);
    DrawTextEx(fontBold, (std::to_string(CollectibleCount / 5)).c_str(), (Vector2){370, 87}, 50, 2, BLACK);
}
