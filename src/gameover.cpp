#include "C:\raylib\raylib\src\raylib.h"
#include "gameover.h"
#include<iostream>
#include<stdio.h>
#include "raylib.h"
#include"button.hpp"

void UpdateGameOver()
{
    Texture2D background= LoadTexture("./images/back.png");
    Button playagainbutton{"./images/replay.png",{80,700},0.35};
     Button menu{"./images/menu.png",{1100,700},0.65};
    Texture2D gameover=LoadTexture("./images/game.png");
    Sound sound=LoadSound("./Audio/music.mp3");
    
        if (IsKeyPressed(KEY_SPACE))
        {
            PlaySound(sound);
        }
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed =IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
         if(playagainbutton.isPressed(mousePosition , mousePressed))
         {
             std::cout<<"Play again button is pressed"<<std::endl;
         }
      if(menu.isPressed(mousePosition,mousePressed))
        {
              std::cout<<"Menu is pressed"<<std::endl;
        }
       
       
    }
    UnloadTexture(background);
    


    


void DrawGameOver()
{
     
        ClearBackground(BLACK);
        DrawTexture(background,0,0,WHITE);
        DrawTexture(gameover,500,300,WHITE);
        playagainbutton.Draw();
        menu.Draw();
    DrawText("Game Over - Press ENTER to Return to Menu", 100, 100, 20, DARKGRAY);
}