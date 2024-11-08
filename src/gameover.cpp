#include "C:\raylib\raylib\src\raylib.h"
#include "gameover.h"
#include "globals.h"
#include <string> 

void UpdateGameOver()
{
    // Update logic for the game over screen
}

void DrawGameOver()
{
    DrawText("Game Over - Press ENTER to Return to Menu", 100, 100, 20, DARKGRAY);
     DrawText(("You earned total " + std::to_string(coinsCollected) + " coins").c_str(), 500, 450, 20, WHITE);
}