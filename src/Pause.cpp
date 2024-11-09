#include "C:\raylib\raylib\src\raylib.h"
#include "Pause.h"
#include <iostream>
#include <string>
#include "collectibles.h"

void UpdatePause()
{
    // pause
}

void DrawPause()
{
    DrawRectangle(0, 0, 1260, 700, Fade(DARKGRAY, 0.8f));
    DrawText("PAUSED", 550, 400, 40, WHITE);
    DrawText(("You earned total " + std::to_string(CollectibleCount) + " points").c_str(), 500, 450, 20, WHITE);
    DrawText("Press P to move to the next level", 500, 500, 20, WHITE);
}