#include "raylib.h"
#include "Pause2.h"
#include <iostream>
#include "collectibles.h"
#include "globals.h"

void UpdatePause2()
{
    // pause
}

void DrawPause2()
{
    DrawRectangle(0, 0, 1400, 900, Fade(DARKGRAY, 0.8f));
    DrawText("YOU WIN", 550, 400, 40, GREEN);
    DrawText(("You earned total " + std::to_string(coinsCollected) + " coinss").c_str(), 500, 450, 20, WHITE);
    DrawText("Press L to move to the next level", 500, 500, 20, WHITE);
}