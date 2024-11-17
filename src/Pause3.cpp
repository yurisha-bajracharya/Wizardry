#include <raylib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "Pause3.h"
#include "globals.h"
#include "level3.h"
bool imageload = false;

void updatePause3()
{
    // pause
}

Texture2D winner;
void drawPause3()
{
    if (!imageload)
    {
        winner = LoadTexture("images/winner.png");
        imageload = true;
    }
    DrawTexture(winner, 0, 0, WHITE);
    DrawText("YOU MADE IT", 550, 40, 40, GREEN);
}