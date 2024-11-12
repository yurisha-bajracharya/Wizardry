#include "C:\raylib\raylib\src\raylib.h"
#include "menu.h"
#include "button.hPP"
    Texture2D backgroundm;
    Texture2D broom;
    Texture2D stand;
    Button startButton;
    Button aboutButton;
    Button exitButton;
    Music musicm;
void InitMenu()
{
    backgroundm= LoadTexture("./images/ok.png");
    broom = LoadTexture("./images/cute.png");
    stand= LoadTexture("./images/stand.png");
    musicm=LoadMusicStream("./Audio/main.mp3");
    startButton=Button("./images/start.png",{1155,280},0.8);
    aboutButton=Button("./images/about.png",{1155,380},0.8);
    exitButton=Button("./images/exit.png",{1155,480},0.8);
}

void UpdateMenu()
{
    // Update logic for the menu
}

void DrawMenu()
{
    DrawTexture(backgroundm,0,0,WHITE);
    DrawText("Main Menu - Press ENTER to Start", 100, 100, 20, DARKGRAY);
}