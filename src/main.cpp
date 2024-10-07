#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "menu.h"
#include "level1.h"
#include "level2.h"
#include "gameover.h"
#include "collectibles.h"
#include "character.h"
#include "Pause.h"

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

enum GameState
{
    MENU = 0,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    PAUSE
};

int main()
{
    InitWindow(1400, 900, "Wizardry");
    SetTargetFPS(60);
    cout << "Window Initialized" << endl;
    float startTime = 0.0f;
    float elapsedTime = 0.0f;
    float endTime = 30.0f;
    float RemainingTime = 0.0f;
    // Current state of the game
    GameState currentState = MENU;
    Collectibles collectible;
    Texture2D texture1 = {0}, texture2 = {0}; // Initializing texture to 0 because if the variable texture1 is declared but not initialized before the switch statement, this can cause issues if the control jumps directly to a case that uses texture1. AND before the while(!WindowShouldClose()) loop, because I donot want the image to be loaded and unloaded multiple times. I want it to be loaded once and used throughout the game.
    texture1 = collectible.LoadTexture("./images/polyjuice_potion.png");
    texture2 = collectible.LoadTexture("./images/expelliarmus.png");
    Image charimg = LoadImage("./images/hpright.png");
    ImageResize(&charimg, 100, 100);
    Texture2D character = LoadTextureFromImage(charimg);

    // Load cloud texture
    Texture2D cloud = LoadTexture("./images/bgclouds.png");
    const int numClouds = 2;           // number of clouds
    Vector2 cloudPositions[numClouds]; // position of clouds

    // Initialize cloud positions with random values
    for (int i = 0; i < numClouds; i++)
    {
        cloudPositions[i].x = GetRandomValue(0, GetScreenWidth() - cloud.width);
        cloudPositions[i].y = GetRandomValue(0, GetScreenHeight() - cloud.height);
    }

    while (!WindowShouldClose())
    {
        elapsedTime = GetTime() - startTime;
        RemainingTime = endTime - elapsedTime;
        switch (currentState)
        {
        case MENU:
            UpdateMenu();
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = LEVEL1;
                startTime = GetTime();
            }
            break;

        case LEVEL1:
            UpdateLevel1();
            if (RemainingTime <= 0) /* time up*/
            {
                RemainingTime = 0;
                currentState = PAUSE;
            }
            if (IsKeyDown(KEY_L))
            {
                currentState = LEVEL2;
            }
            break;

        case LEVEL2:
            UpdateLevel2();
            if (IsKeyDown(KEY_W)) /* condition for winning */
            {
                currentState = GAMEOVER; // Game over after winning
            }
            else if (IsKeyDown(KEY_W)) /* condition for losing */
            {
                currentState = GAMEOVER; // Game over after losing
            }
            break;

        case GAMEOVER:
            UpdateGameOver();
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = MENU; // Return to the main menu
            }
            break;

        case PAUSE:
            UpdatePause();
            if (IsKeyPressed(KEY_P))
            {
                currentState = LEVEL2; // Move to the next level
            }
            break;
        }
        // Update cloud positions
        for (int i = 0; i < numClouds; i++)
        {
            cloudPositions[i].x += 1;

            // Reset cloud position if it moves off the screen
            if (cloudPositions[i].x > GetScreenWidth())
            {
                cloudPositions[i].x = GetRandomValue(-cloud.width, GetScreenWidth() - cloud.width);
                cloudPositions[i].y = GetRandomValue(-cloud.height, GetScreenHeight() - cloud.height);
            }
        }

        // Draw game elements based on the current state
        BeginDrawing();
        ClearBackground(green);

        switch (currentState)
        {
        case MENU:
            DrawMenu();
            break;

        case LEVEL1:
            // adding image on background
            ClearBackground(GRAY);
            collectible.Draw(texture1, texture2);
            DrawLevel1(character);

            // Draw clouds
            for (int i = 0; i < numClouds; i++)
            {
                DrawTexture(cloud, cloudPositions[i].x, cloudPositions[i].y, WHITE);
            }
            RemainingTime = endTime - elapsedTime;
            // Draw Timer
            DrawText(TextFormat("Remaining Time: %.2f", RemainingTime), 10, 10, 40, BLACK);
            break;

        case LEVEL2:
            ClearBackground(darkGreen);
            DrawLevel2();
            break;

        case GAMEOVER:
            DrawGameOver();
            break;

        case PAUSE:
            DrawPause();
            break;
        }

        EndDrawing();
    }
    UnloadTexture(cloud);
    CloseWindow();
    return 0;
}
