#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "collectibles.h"
#include "string"
#include "button.h"
#include "globals.h"
#include "pause.h"

Texture2D pausebg;

void InitPause()
{
    pausebg = LoadTexture("./images/pausebg.png");
}

void UnloadPause()
{
    UnloadTexture(pausebg);
}

void UpdatePause()
{
}

void DrawPause()
{
    DrawTexture(pausebg, 0, 0, WHITE);
}
