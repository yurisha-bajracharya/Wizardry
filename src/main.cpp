#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "menu.h"
#include "level1.h"
#include "level2.h"
#include "gameover.h"
#include "collectibles.h"
#include "character.h"
#include "Pause.h"
#include "globals.h"

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

enum GameState
{
    MENU = 0,
    MAP,
    LEVEL1,
    LEVEL2,
    GAMEOVER,
    PAUSE
};

Collectibles collectible;

int main()
{
    InitWindow(1260, 700, "Wizardry");//changed size of window
    SetTargetFPS(60);
    cout << "Window Initialized" << endl;
    Texture2D backgroundlevel1 = LoadTexture("./images/bg1.png");
    float startTime = 0.0f;
    float elapsedTime = 0.0f;
    float endTime = 90.0f;
    float RemainingTime = 0.0f;

    Color OLIVE_GREEN = {107, 142, 35, 255};
    // Current state of the game
    GameState currentState = MENU;
    Collectibles collectible;
    Texture2D currentMapImage = {0};

    Texture2D texture = collectible.LoadTexture("./images/snitch.png");
    Texture2D bludgerTexture = collectible.LoadTexture("./images/bludgers.png");

    // Load cloud texture
    Texture2D cloud = LoadTexture("./images/bgclouds.png");
    const int numClouds = 5;           // number of clouds
    Vector2 cloudPositions[numClouds]; // position of clouds

    // Initialize cloud positions with random values
    for (int i = 0; i < numClouds; i++)
    {
        cloudPositions[i].x = GetRandomValue(0, GetScreenWidth() - cloud.width);
        cloudPositions[i].y = GetRandomValue(0, GetScreenHeight() - cloud.height);
    }

    // Load map and highlighted images
    Texture2D mapImage = LoadTexture("./images/mapimg.png");
    Texture2D hogsmeadehovered = LoadTexture("./images/hogsmeadehovered.png");
    Texture2D forbiddenhovered = LoadTexture("./images/forbiddenhovered.png");
    Texture2D mainbuildinghovered = LoadTexture("./images/mainbuildinghovered.png");

    // defining areas for each level
   // Defining areas for each level adjusted for a window size of 1260 x 700
Rectangle hogsmeadeArea = {90, 155, 180, 117};       // Hogsmeade area
Rectangle forbiddenArea = {1080, 232, 180, 117};     // Forbidden area
Rectangle mainbuildingArea = {720, 466, 270, 233};    // Main building area


    while (!WindowShouldClose())
    {
        elapsedTime = GetTime() - startTime;
        RemainingTime = endTime - elapsedTime;
        Vector2 mousePosition = GetMousePosition();
        bool isHoveringHogsmeade = CheckCollisionPointRec(mousePosition, hogsmeadeArea);
        bool isHoveringForbiddenForest = CheckCollisionPointRec(mousePosition, forbiddenArea);
        bool isHoveringMainBuilding = CheckCollisionPointRec(mousePosition, mainbuildingArea);

        switch (currentState)
        {
        case MENU:
            UpdateMenu();
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = MAP;
                startTime = GetTime();
            }
            break;

        case MAP:
            if (isHoveringHogsmeade)
            {
                currentMapImage = hogsmeadehovered;
            }
            else if (isHoveringForbiddenForest)
            {
                currentMapImage = forbiddenhovered;
            }
            else if (isHoveringMainBuilding)
            {
                currentMapImage = mainbuildinghovered;
            }
            else
            {
                currentMapImage = mapImage;
            }
            if (isHoveringHogsmeade && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentState = LEVEL1;
                startTime = GetTime();
                InitLevel1();
            }
            else if (isHoveringForbiddenForest && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentState = LEVEL2;
                startTime = GetTime();
            }
            else if (isHoveringMainBuilding && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                currentState = GAMEOVER;
                startTime = GetTime();
            }
            break;

        case LEVEL1:
            UpdateLevel1();
            collectible.UpdateBludgers();
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

        case MAP:
            DrawTexture(currentMapImage, 0, 0, WHITE);
            break;

        case LEVEL1:
            // adding image on background
            ClearBackground(GRAY);
            DrawTexture(backgroundlevel1, 0, 0, WHITE);
            // collectible.Draw(texture);
            DrawLevel1();
            DrawCollectible(texture);
            DrawBludgers(bludgerTexture);

            // Draw clouds
            for (int i = 0; i < numClouds; i++)
            {
                DrawTexture(cloud, cloudPositions[i].x, cloudPositions[i].y, WHITE);
            }
            RemainingTime = endTime - elapsedTime;
            // Draw Timer
            DrawText(TextFormat("Remaining Time: %.2f", RemainingTime), 510, 30, 40, OLIVE_GREEN);
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