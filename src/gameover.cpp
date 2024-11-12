#include "C:\raylib\raylib\src\raylib.h"
#include "gameover.h"
#include <iostream>
#include <stdio.h>
#include "button.hpp"

Texture2D background;
Sound sound;
Button playagainbutton;
Button menu;
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
    playagainbutton = Button("./images/replay.png", {80, 700}, 0.35); // syntax: Button(const char *imagepath, Vector2 imageposition, float scale)
    menu = Button("./images/menu.png", {1100, 700}, 0.65);
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
    Vector2 mousePosition = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    if (playagainbutton.isPressed(mousePosition, mousePressed))
    {
        std::cout << "Play again button is pressed" << std::endl;
    }
    if (menu.isPressed(mousePosition, mousePressed))
    {
        std::cout << "Menu is pressed" << std::endl;
    }
}

void DrawGameOver()
{
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTexture(gameoverimg, 0, 0, WHITE);
    playagainbutton.Draw();
    menu.Draw();
    DrawText("Game Over - Press ENTER to Return toothee Menu", 100, 100, 20, DARKGRAY);
}
