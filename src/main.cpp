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
#include "Pause3.h"
#include "globals.h"
#include "button.h"
#include "unload.h"

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
    PAUSE2,
    PAUSE3
};

Collectibles collectible;
bool extraLifeCalled = false;
bool extraHintCalled = false;
bool exitWindow = false;
Button playagainbutton;
Button menubutton;
Button nextbutton;
Button homebutton;
Button exit2button;
Button replaybutton;
Button startButton;
Button exitButton;

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
    void Unload();
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
    InitFonts();
    InitLevel1();
    InitPause();
    InitPause1();
    InitPause2();
    InitGameOver();
    Sound winmusic = LoadSound("./Audio/win.mp3");

    Texture2D newgame = LoadTexture("./images/newgame.png");
    Texture2D menuimg = LoadTexture("./images/menuimg.png");
    Texture2D next = LoadTexture("./images/next.png");
    Texture2D home = LoadTexture("./images/homebutton.png");
    Texture2D exit2 = LoadTexture("./images/exit2.png");
    Texture2D replay = LoadTexture("./images/replay.png");
    Texture2D startB = LoadTexture("./images/start.png");
    Texture2D exitB = LoadTexture("./images/exit.png");
    playagainbutton.SetPosition(80, 600);
    menubutton.SetPosition(920, 600);
    startButton.SetPosition(1045, 290);
    exitButton.SetPosition(1045, 390);
    startButton.scale = 0.8f;
    exitButton.scale = 0.8f;
    playagainbutton.scale = 0.65f;
    menubutton.scale = 0.45f;
    nextbutton.SetPosition(920, 600);
    nextbutton.scale = 0.45f;
    homebutton.SetPosition(1090, 0);
    homebutton.scale = 1.0f;
    exit2button.SetPosition(1200, 0);
    exit2button.scale = 1.0f;
    replaybutton.SetPosition(1145, 0);
    replaybutton.scale = 1.0f;
    Sound gameovermusic = LoadSound("./Audio/music.mp3");

    while (!WindowShouldClose() && !exitWindow)
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
            updateMenu();
            // if (IsKeyPressed(KEY_ENTER))
            // {
            //     currentState = MAP;
            //     startTime = GetTime();
            // }
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                if (startButton.isPressed(mousePosition, mousePressed, startButton.position, startButton.scale, startB.width, startB.height))
                {
                    currentState = MAP; // Move to map
                }
                if (exitButton.isPressed(mousePosition, mousePressed, exitButton.position, exitButton.scale, exitB.width, exitB.height))
                {
                    Unload();
                    exitWindow = true;
                }
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
                currentState = PAUSE1;
                startTime = GetTime();
            }
            else if (isHoveringMainBuilding && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                StopSound(mapbgm);
                // if (!IsSoundPlaying(hovered))
                // {
                //     PlaySound(hovered);
                // }
                currentState = PAUSE2;
                startTime = GetTime();
                // InitGameOver();
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
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                if (homebutton.isPressed(mousePosition, mousePressed, homebutton.position, homebutton.scale, home.width, home.height))
                {
                    RemainingTime = 120.0f;
                    CollectibleCount = 0;
                    Initnew2();
                    initNewLevel3();
                    initNewMenu();
                    currentState = MAP; // Move to map
                }
                if (exit2button.isPressed(mousePosition, mousePressed, exit2button.position, exit2button.scale, exit2.width, exit2.height))
                {
                    Unload();
                    exitWindow = true;
                }
                if (replaybutton.isPressed(mousePosition, mousePressed, replaybutton.position, replaybutton.scale, replay.width, replay.height))
                {
                    RemainingTime = 120.0f;
                    CollectibleCount = 0;
                    initNewLevel3();
                    initNewMenu();
                    Initnew2();
                    currentState = LEVEL1; // Move to the next level
                }
            }
            break;
        }
        case LEVEL3:
        {
            if (IsSoundPlaying(gameovermusic))
            {
                StopSound(gameovermusic);
            }
            if (!extraHintCalled)
            {
                extraHint();
                extraHintCalled = true;
            }
            updateLevel3();
            if (riddleComplete && isWon && IsKeyDown(KEY_Q)) // condition for winning to go to pause3 screen
            {
                currentState = PAUSE3;
            }

            if (riddleComplete && !isWon && IsKeyDown(KEY_Q)) // condition for loosing to go to gameover page
            {
                currentState = GAMEOVER;
            }

            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                if (homebutton.isPressed(mousePosition, mousePressed, homebutton.position, homebutton.scale, home.width, home.height))
                {
                    RemainingTime = 120.0f;
                    CollectibleCount = 0;
                    Initnew2();
                    currentState = MAP;
                    initNewLevel3(); // Move to map
                }
                if (exit2button.isPressed(mousePosition, mousePressed, exit2button.position, exit2button.scale, exit2.width, exit2.height))
                {
                    Unload();
                    exitWindow = true;
                }
                if (replaybutton.isPressed(mousePosition, mousePressed, replaybutton.position, replaybutton.scale, replay.width, replay.height))
                {

                    // RemainingTime=120.0f;
                    // CollectibleCount=0;
                    // Initnew2();
                    currentState = LEVEL3;
                    initNewLevel3(); // Move to the next level
                }
            }
            // if (IsKeyDown(KEY_O)) /* condition for winning */
            // {
            //     currentState = GAMEOVER; // Game over after winning
            // }
            // else if (IsKeyDown(KEY_O)) /* condition for losing */
            // {
            //     currentState = GAMEOVER; // Game over after losing
            // }
            break;
        }

        case GAMEOVER:
        {
            if (!IsSoundPlaying(gameovermusic))
            {
                PlaySound(gameovermusic);
            }
            UpdateGameOver();
            // if (IsKeyPressed(KEY_ENTER))
            // {
            //     currentState = MENU; // Return to the main menu
            // }
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            {
                if (playagainbutton.isPressed(mousePosition, mousePressed, playagainbutton.position, playagainbutton.scale, newgame.width, newgame.height))
                {
                    RemainingTime = 120.0f;
                    CollectibleCount = 0;
                    Initnew2();
                    currentState = PAUSE; // Move to the next level
                    cout << "Play again button is pressed" << endl;

                    StopSound(gameovermusic);
                }
                if (menubutton.isPressed(mousePosition, mousePressed, menubutton.position, menubutton.scale, menuimg.width, menuimg.height))
                {
                    RemainingTime = 120.0f;
                    CollectibleCount = 0;
                    Initnew2();
                    currentState = MENU;
                    initNewMenu();
                    initNewLevel3();
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
                if (nextbutton.isPressed(mousePosition, mousePressed, nextbutton.position, nextbutton.scale, next.width, next.height))
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
                if (nextbutton.isPressed(mousePosition, mousePressed, nextbutton.position, nextbutton.scale, next.width, next.height))
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
                if (nextbutton.isPressed(mousePosition, mousePressed, nextbutton.position, nextbutton.scale, next.width, next.height))
                {
                    currentState = LEVEL3; // Move to the next level
                    cout << "level2 reached" << endl;
                }
            }
            break;
        }
        case PAUSE3:
        {
            if (!IsSoundPlaying(winmusic))
            {
                PlaySound(winmusic);
            }
            updatePause3();
            bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
            if (menubutton.isPressed(mousePosition, mousePressed, menubutton.position, menubutton.scale, menuimg.width, menuimg.height))
            {
                RemainingTime = 120.0f;
                CollectibleCount = 0;
                Initnew2();
                currentState = MENU;
                cout << "Menu is pressed" << endl;
                initNewMenu();
                initNewLevel3();
                StopSound(gameovermusic);
            }
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
            drawMenu();
            startButton.Draw(startB, startButton.scale);
            exitButton.Draw(exitB, exitButton.scale);
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
            exit2button.Draw(exit2, exit2button.scale);
            homebutton.Draw(home, homebutton.scale);
            replaybutton.Draw(replay, replaybutton.scale);
            break;
        case LEVEL3:
            ClearBackground(darkGreen);
            drawLevel3();
            exit2button.Draw(exit2, exit2button.scale);
            homebutton.Draw(home, homebutton.scale);
            replaybutton.Draw(replay, replaybutton.scale);
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

        case PAUSE3:
            drawPause3();
            menubutton.Draw(menuimg, menubutton.scale);
            break;
        }
        EndDrawing();
    }
    Unload();
    UnloadSound(mapbgm);
    UnloadSound(level1Music);
    UnloadSound(gameovermusic);
    UnloadTexture(cloud);
    UnloadSound(hovered);
    CloseWindow();
    return 0;
}
