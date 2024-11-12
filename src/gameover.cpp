#include "C:\raylib\raylib\src\raylib.h"
#include "gameover.h"
#include <iostream>
#include <stdio.h>
#include "button.h"

Texture2D background;

Texture2D gameoverimg;

void InitGameOver()
{
    std::cout << "initializing game over screen" << std::endl;
    background = LoadTexture("./images/back.png");
    if (background.id == 0)
        std::cerr << "background not loaded" << std::endl;
    gameoverimg = LoadTexture("./images/gameover.png");
    std::cout << "game over screen initialized" << std::endl;
}

void UnloadGameOver()
{
    UnloadTexture(background);
    UnloadTexture(gameoverimg);
}
void UpdateGameOver()
{
}

void DrawGameOver()
{
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    // to scale image also
    DrawTextureEx(gameoverimg, {800, 200}, 0, 0.5f, WHITE);
}
