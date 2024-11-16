#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include  "menu.h"
#include <string.h>
#define MAX_LINES 6 // Maximum number of lines in the area
#define MAX_CHARACTERS_PER_LINE 35  // Maximum characters per line before wrapping


//Texture objects
Texture2D menubg;
Texture2D broom;
Texture2D stand;
Music musicm;

//variables

    Vector2 initialPosition;
    Vector2 targetPosition;
    Vector2 standPosition;
  bool isBroom = true;
   bool isReachedTarget = false;
   bool timeForText = false;
   bool exit1 = false;
  
    int frameCount=6;
  Rectangle frameRec;
    Rectangle frameRec2;
   int currentframe=0;
   int frameCounter=0;
   int frameSpeed= 5;
   float delayTime=1.5f;
   float timeElapsed=0.0f;




// Text messages
const char* messages[] = {
    "Hello There!!! Ready to conquer?",
    "I hope you are ready.",
    "Three battles stand between you and victory.",
    "Begin at level one(Quidditch),if   you value survival",
    "Good luck with the Game.",
    " "
};

     // Font and text size
   Font font = GetFontDefault();
    int messageIndex = 0;  // Current message being displayed
     int charIndex = 0;     // Number of characters displayed
    float typingSpeed = 0.05f;  // Typing speed (lower = faster)
    float timePassed = 0.0f;  // Time elapsed for typing
    int totalMessages = sizeof(messages) / sizeof(messages[0]);

    Rectangle textArea;  // Area to display text (x, y, width, height)
    int lineHeight = 40;  // Line height for spacing between lines


void updateMenu()
{
static bool initialized = false; // Static variable to track initialization
if (!initialized)
{
  
    menubg=LoadTexture("images/ok.png");
    broom=LoadTexture("images/cute.png");
    stand=LoadTexture("images/stand.png");
    musicm=LoadMusicStream("Audio/main.mp3");
    PlayMusicStream(musicm);


  frameRec={0.0f,0.0f,(float)broom.width,(float)broom.height};
 frameRec2={0.0f,0.0f,(float)stand.width,(float)stand.height}; 
    //Initialize positions

    initialPosition={0, 700/*screenheight*/- frameRec.height-5};//initial position of the image
    targetPosition={1100/*screenwidth*//2.0f- frameRec.width/4.0f, initialPosition.y};
    standPosition={1100/*screenwidth*//2.0f- frameRec2.width/4.0f,700-frameRec2.height};

  
textArea = { 720, 560, 0, 100 };
 initialized=true;
}



      UpdateMusicStream(musicm);

//*****************For updating the broom frame until final position has reached************************

if( isBroom &&initialPosition.x < targetPosition.x)
{
  frameCounter++;
 
 if(frameCounter>=(60/frameSpeed))
 {
  frameCounter=0;
  currentframe++;

  if(currentframe>= frameCount) currentframe=0;
  frameRec.x=(float)currentframe* frameRec.width;//update the frame rectangle
}
//move the character 
initialPosition.x += 1.1f;//adjust the movement from here
}
if(!isReachedTarget && initialPosition.x >=targetPosition.x)
{
   isReachedTarget=true;
}
if (isReachedTarget && isBroom)
{
   timeElapsed+=GetFrameTime();
   if(timeElapsed>=delayTime)
   {
      isBroom= false;
   }
}
if (!isBroom)
{
timeForText=true;
}

//******************************FOR TEXT **************************************************
 // Check if space is pressed to load the next message
 if(timeForText)
 {
        if (IsKeyPressed(KEY_SPACE) && messageIndex < totalMessages-1 ) {
            messageIndex++;  // Move to the next message
            charIndex = 0;   // Reset character index for new message
            timePassed = 0.0f;  // Reset timer
        }

        // Update the time and characters for typing effect 
        timePassed += GetFrameTime();
        if (timePassed >= typingSpeed && charIndex < static_cast<int> (strlen(messages[messageIndex]))) {
            charIndex++;
            timePassed = 0.0f;  // Reset timer for next character
        }
 }

}

void drawMenu()
{
    ClearBackground(BLACK);
    DrawTexture(menubg,0,0,WHITE);

//*********************************FOR SWITCHING IMAGES****************************************
if(isBroom){
DrawTextureRec(broom, frameRec, initialPosition,WHITE);
}
else
{
DrawTextureRec(stand,frameRec2, standPosition,WHITE);
}
//*********************************FOR TEXT*************************************************
 // Draw text with line wrapping
    if (timeForText) {
        int line = 0;
        int charCount = 0;
        for (int i = 0; i < charIndex && line < MAX_LINES; i++) {
            if (messages[messageIndex][i] == '\n' || charCount >= MAX_CHARACTERS_PER_LINE) {
                line++;
                charCount = 0;
            }
            if (line < MAX_LINES) {
                DrawTextEx(font, TextFormat("%c", messages[messageIndex][i]), 
                           (Vector2){textArea.x + charCount * 15, textArea.y + line * lineHeight}, 
                           25, 2, WHITE);
                charCount++;
            }
        }
         
        // Draw an instruction to press space for the next message
    if (timeForText && messageIndex < totalMessages-1 && charIndex== static_cast<int>(strlen(messages[messageIndex])))
     {
            DrawText("Press SPACE for next message", 900, 670, 20, WHITE);
            
        }
        }

}

void unloadMenu()
{
    UnloadTexture(menubg);
    UnloadTexture(broom);
    UnloadTexture(stand);
    UnloadMusicStream(musicm);
}