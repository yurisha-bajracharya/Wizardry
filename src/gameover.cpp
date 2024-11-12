#include "C:\raylib\raylib\src\raylib.h"
#include "gameover.h"
#include <iostream>
#include <stdio.h>
#include "button.h"

Texture2D background;
Sound sound;

Texture2D gameoverimg;

void InitGameOver()
{
    std::cout << "initializing game over screen" << std::endl;
    background = LoadTexture("./images/back.png");
    if (background.id == 0)
        std::cerr << "background not loaded" << std::endl;
    gameoverimg = LoadTexture("./images/gameover.png");
    if (gameoverimg.id == 0)
        std::cerr << "gameover not loaded" << std::endl;
    sound = LoadSound("./Audio/music.mp3");
    if (sound.frameCount == 0)
        std::cerr << "sound not loaded" << std::endl;

    std::cout << "game over screen initialized" << std::endl;
}

void UnloadGameOver()
{
    UnloadTexture(background);
    UnloadTexture(gameoverimg);
    UnloadSound(sound);
}
void UpdateGameOver()
{

    if (IsKeyPressed(KEY_SPACE))
    {
        PlaySound(sound);
    }
}

void DrawGameOver()
{
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(gameoverimg, 0, 0, WHITE);

    DrawText("Game Over - Press ENTER to Return toothee Menuuuu", 100, 100, 20, DARKGRAY);
}
