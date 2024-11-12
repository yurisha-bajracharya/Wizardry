#include "C:\raylib\raylib\src\raylib.h"
#include "Pause1.h"
#include <iostream>
#include "collectibles.h"
#include "string"
#include "button.h"
#include "globals.h"

Texture2D pause2bg;
Font myfont3;
Font myfont4;

void InitPause2()
{
    pause2bg = LoadTexture("./images/pause2bg.png");
    myfont3 = LoadFontEx("./font/Poppins-Bold.ttf", 200, 0, 0);
    myfont4 = LoadFontEx("./font/Poppins-Regular.ttf", 200, 0, 0); // syntax: Font LoadFontEx(const char *fileName, int fontSize, int charsCount, int *fontChars);
}

void UnloadPause2()
{
    UnloadTexture(pause2bg);
    UnloadFont(myfont3);
    UnloadFont(myfont4);
}

void UpdatePause2()
{
}

void DrawPause2()
{
    DrawTexture(pause2bg, 0, 0, WHITE);
    DrawTextEx(myfont4, (std::to_string(coinsCollected)).c_str(), (Vector2){380, 33}, 43, 2, BLACK);
    DrawTextEx(myfont3, (std::to_string(coinsCollected / 3)).c_str(), (Vector2){380, 83}, 50, 2, BLACK);
}
