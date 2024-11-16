#include<raylib.h>
#include "C:\raylib\raylib\src\raylib.h"
#include<iostream>
#include "Pause3.h"
#include "globals.h"

void updatePause3()
{
    // pause
}

void drawPause3()
{
    DrawRectangle(0, 0, 1400, 900, Fade(DARKGRAY, 0.8f));
    DrawText("GAME OVER", 550, 400, 40, GREEN);
    DrawText(("You scored total " + std::to_string(score) + " score").c_str(), 500, 450, 20, WHITE);
    DrawText("Press O to move to the next level", 500, 500, 20, WHITE);
}