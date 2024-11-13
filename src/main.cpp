#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "menu.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "gameover.h"
#include "collectibles.h"
#include "character.h"
#include "Pause.h"
#include "Pause1.h"
#include "Pause2.h"
#include "globals.h"
#include "button.h"

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

enum GameState
{
    MENU = 0,
    MAP,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    GAMEOVER,
    PAUSE,
    PAUSE1,
    PAUSE2
};

Collectibles collectible;
bool extraLifeCalled = false;
// Button nextLevelButton;
Button playagainbutton;
Button menubutton;
Button nextbutton;

int main()
{
    InitWindow(1260, 700, "Wizardry"); // changed size of window
    InitAudioDevice();
    SetTargetFPS(60);
    cout << "Window Initialized" << endl;
    Texture2D backgroundlevel1 = LoadTexture("./images/level1bg.png");
    float startTime = 0.0f;
    float elapsedTime = 0.0f;
    float endTime = 120.0f;
    float RemainingTime = 0.0f;

    // Color OLIVE_GREEN = {107, 142, 35, 255};
    //  Current state of the game

    GameState currentState = MENU;
    Collectibles collectible;
    Texture2D currentMapImage = {0};

    Texture2D texture = collectible.LoadTexture("./images/snitch.png");
    Texture2D bludgerTexture = collectible.LoadTexture("./images/bludgers.png");

    // Load cloud texture
    Texture2D cloud = LoadTexture("./images/bgclouds.png");
    const int numClouds = 5;           // number of clouds
    Vector2 cloudPositions[numClouds]; // position of clouds
    Sound mapbgm = LoadSound("./Audio/mapbgm.mp3");
    Sound level1Music = LoadSound("./Audio/level1.mp3");
    // to check if sound loaded or not
    if (mapbgm.frameCount == 0)
    {
        cout << "mapbgm Sound not loaded" << endl;
    }
    else
    {
        cout << "Sound loaded" << endl;
    }
    Sound hovered = LoadSound("./Audio/hovered.mp3");

    // Initialize cloud positions with random values
    for (int i = 0; i < numClouds; i++)
    {
        cloudPositions[i].x = GetRandomValue(0, GetScreenWidth() - cloud.width);
        cloudPositions[i].y = GetRandomValue(0, GetScreenHeight() - cloud.height);
    }

    // Load map and highlighted images
    Texture2D mapImage = LoadTexture("./images/mapimg.png");
    Texture2D quidditchhovered = LoadTexture("./images/quidditchhovered.png");
    Texture2D forbiddenhovered = LoadTexture("./images/forbiddenhovered.png");
    Texture2D mainbuildinghovered = LoadTexture("./images/mainbuildinghovered.png");

    // defining areas for each level
    // Defining areas for each level adjusted for a window size of 1260 x 700
    Rectangle quidditchArea = {500, 260, 180, 150};    // Quidditch area
    Rectangle forbiddenArea = {1080, 232, 180, 117};   // Forbidden area
    Rectangle mainbuildingArea = {720, 466, 270, 233}; // Main building area

    // initializing
    InitLevel1();
    InitPause();
    InitPause1();
    InitPause2();
    InitGameOver();
    Texture2D newgame = LoadTexture("./images/newgame.png");
    Texture2D menuimg = LoadTexture("./images/menuimg.png");
    Texture2D next = LoadTexture("./images/next.png");
    playagainbutton.SetPosition(80, 600);
    menubutton.SetPosition(920, 600);
    playagainbutton.scale = 0.65f;
    menubutton.scale = 0.45f;
    nextbutton.SetPosition(920, 600);
    nextbutton.scale = 0.45f;
    Sound gameovermusic = LoadSound("./Audio/music.mp3");

    while (!WindowShouldClose())
    {
        elapsedTime = GetTime() - startTime;
        RemainingTime = endTime - elapsedTime;
        Vector2 mousePosition = GetMousePosition();
        bool isHoveringQuidditch = CheckCollisionPointRec(mousePosition, quidditchArea);
        bool isHoveringForbiddenForest = CheckCollisionPointRec(mousePosition, forbiddenArea);
        bool isHoveringMainBuilding = CheckCollisionPointRec(mousePosition, mainbuildingArea);

        switch (currentState)
        {
        case MENU:
        {
            UpdateMenu();
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = MAP;
                startTime = GetTime();
            }
            break;
        }

        case MAP:
        {
            if (!IsSoundPlaying(mapbgm))
            {
                PlaySound(mapbgm);
            }
            if (isHoveringQuidditch)
            {
                currentMapImage = quidditchhovered;
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
            if (isHoveringQuidditch && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                StopSound(mapbgm);
                if (!IsSoundPlaying(hovered))
                {
                    PlaySound(hovered);
                }
                currentState = PAUSE;
            }
            else if (isHoveringForbiddenForest && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                StopSound(mapbgm);
                if (!IsSoundPlaying(hovered))
                {
                    PlaySound(hovered);
                }
                currentState = LEVEL2;
                startTime = GetTime();
            }
            else if (isHoveringMainBuilding && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                StopSound(mapbgm);
                if (!IsSoundPlaying(hovered))
                {
                    PlaySound(hovered);
                }
                currentState = GAMEOVER;
                startTime = GetTime();
                InitGameOver();
            }
            // to stop playing sound after mapimg is not displayed
            break;
        }

        case LEVEL1:
        {
            if (IsSoundPlaying(gameovermusic))
            {
                StopSound(gameovermusic);
            }
            if (!IsSoundPlaying(level1Music))
            {
                PlaySound(level1Music);
            }
            UpdateLevel1();
            // collectible.UpdateBludgers();
            if (RemainingTime <= 0) /* time up*/
            {
                RemainingTime = 0;
                StopSound(level1Music);
                currentState = PAUSE1;
            }
            if (IsKeyDown(KEY_L))
            {
                StopSound(level1Music);
                currentState = PAUSE1;
            }
            break;
        }

        case LEVEL2:
        {
            if (IsSoundPlaying(gameovermusic))
            {
                StopSound(gameovermusic);
            }
            if (!extraLifeCalled)
            {
                extraLife();
                extraLifeCalled = true;
            }
            UpdateLevel2();
            if (gameWon) /* condition for winning */
            {
                currentState = PAUSE2; // Game over after winning
            }
            else if (IsKeyDown(KEY_L))
            {
                StopSound(mapbgm);
                currentState = PAUSE2;
            }
            else if (gameOver) /* condition for losing */
            {
                currentState = GAMEOVER; // Game over after losing
            }
            break;
        }
        case LEVEL3:
        {
            UpdateLevel3();
            if (IsKeyDown(KEY_O)) /* condition for winning */
            {
                currentState = GAMEOVER; // Game over after winning
            }
            else if (IsKeyDown(KEY_O)) /* condition for losing */
            {
                currentState = GAMEOVER; // Game over after losing
            }
            break;
        }

        case GAMEOVER:
        {
            if (!IsSoundPlaying(gameovermusic))
            {
                PlaySound(gameovermusic);
            }
            UpdateGameOver();
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = MENU; // Return to the main menu
            }
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                if (playagainbutton.isPressed(mousePosition, mousePressed, playagainbutton.position, playagainbutton.scale))
                {
                    currentState = PAUSE; // Move to the next level
                    cout << "Play again button is pressed" << endl;
                    StopSound(gameovermusic);
                }
                if (menubutton.isPressed(mousePosition, mousePressed, menubutton.position, menubutton.scale))
                {
                    currentState = MENU;
                    cout << "Menu is pressed" << endl;
                    StopSound(gameovermusic);
                }
            }
            break;
        }

        case PAUSE:
        {
            if (!IsSoundPlaying(gameovermusic))
            {
                PlaySound(gameovermusic);
            }
            UpdatePause();
            if (IsKeyPressed(KEY_P))
            {
                StopSound(mapbgm);
                currentState = LEVEL1; // Move to the next level
                startTime = GetTime();
            }
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                StopSound(mapbgm);
                if (nextbutton.isPressed(mousePosition, mousePressed, nextbutton.position, nextbutton.scale))
                {
                    currentState = LEVEL1; // Move to the next level
                    cout << "level1 reached" << endl;
                    startTime = GetTime();
                }
            }
            break;
        }

        case PAUSE1:
        {
            if (!IsSoundPlaying(gameovermusic))
            {
                PlaySound(gameovermusic);
            }
            UpdatePause1();
            if (IsKeyPressed(KEY_P))
            {
                StopSound(mapbgm);
                currentState = LEVEL2; // Move to the next level
            }
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                StopSound(mapbgm);
                if (nextbutton.isPressed(mousePosition, mousePressed, nextbutton.position, nextbutton.scale))
                {
                    currentState = LEVEL2; // Move to the next level
                    cout << "level2 reached" << endl;
                }
            }
            break;
        }

        case PAUSE2:
        {
            if (!IsSoundPlaying(gameovermusic))
            {
                PlaySound(gameovermusic);
            }
            UpdatePause2();
            if (IsKeyPressed(KEY_L))
            {
                StopSound(mapbgm);
                currentState = LEVEL3; // Move to the next level
            }
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                StopSound(mapbgm);
                if (nextbutton.isPressed(mousePosition, mousePressed, nextbutton.position, nextbutton.scale))
                {
                    currentState = LEVEL3; // Move to the next level
                    cout << "level2 reached" << endl;
                }
            }
            break;
        }
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

            for (int i = 0; i < 3; i++)
            {

                collectible.UpdateBludgers(i);
                collectible.DrawBludgers(i, bludgerTexture);
            };

            // Draw clouds
            for (int i = 0; i < numClouds; i++)
            {
                DrawTexture(cloud, cloudPositions[i].x, cloudPositions[i].y, WHITE);
            }
            RemainingTime = endTime - elapsedTime;
            // Draw Timer
            DrawText(TextFormat("Remaining Time: \n %.2f", RemainingTime), 1052, 49, 19, darkGreen); // syntax: DrawText(const char *text, int posX, int posY, int fontSize, Color color)
            break;

        case LEVEL2:
            ClearBackground(darkGreen);
            DrawLevel2();
            break;
        case LEVEL3:
            ClearBackground(darkGreen);
            DrawLevel3();
            break;

        case GAMEOVER:
            DrawGameOver();
            playagainbutton.Draw(newgame, playagainbutton.scale);
            menubutton.Draw(menuimg, menubutton.scale);
            break;

        case PAUSE:
            DrawPause();
            nextbutton.Draw(next, nextbutton.scale);
            break;

        case PAUSE1:
            DrawPause1();
            nextbutton.Draw(next, nextbutton.scale);
            break;
        case PAUSE2:
            DrawPause2();
            nextbutton.Draw(next, nextbutton.scale);
            break;
        }

        EndDrawing();
    }
    UnloadLevel1();
    UnloadTexture(cloud);
    UnloadGameOver();
    UnloadSound(mapbgm);
    UnloadSound(level1Music);
    UnloadSound(gameovermusic);
    UnloadSound(hovered);
    UnloadPause();
    UnloadPause1();
    UnloadPause2();
    CloseWindow();
    return 0;
}
