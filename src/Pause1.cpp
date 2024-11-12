#include "C:\raylib\raylib\src\raylib.h"
#include "Pause1.h"
#include <iostream>
#include "collectibles.h"
#include "string"
#include "button.h"
#include "globals.h"

Texture2D pause1bg;
Font myfont1;
Font myfont2;

void InitPause1()
{
    pause1bg = LoadTexture("./images/pause1bg.png");
    myfont1 = LoadFontEx("./font/Poppins-Bold.ttf", 200, 0, 0);
    myfont2 = LoadFontEx("./font/Poppins-Regular.ttf", 200, 0, 0); // syntax: Font LoadFontEx(const char *fileName, int fontSize, int charsCount, int *fontChars);
}

void UnloadPause1()
{
    UnloadTexture(pause1bg);
    UnloadFont(myfont1);
    UnloadFont(myfont2);
}

void UpdatePause1()
{
}

void DrawPause1()
{
    DrawTexture(pause1bg, 0, 0, WHITE);
    DrawTextEx(myfont2, (std::to_string(CollectibleCount)).c_str(), (Vector2){390, 36}, 43, 2, BLACK);
    DrawTextEx(myfont1, (std::to_string(CollectibleCount / 5)).c_str(), (Vector2){370, 87}, 50, 2, BLACK);
}
