#include "raylib.h"
#include <iostream>
#include  "menu.h"
#include <string.h>
#include "globals.h"
#define MAX_LINES 6 // Maximum number of lines in the area
#define MAX_CHARACTERS_PER_LINE 35  // Maximum characters per line before wrapping



void Menu::Init() {
    InitAudioDevice();
    theme= LoadMusicStream("Audio/main.mp3");
    background = LoadTexture("images/ok.png");
    broom = LoadTexture("images/cute.png");
    stand = LoadTexture("images/stand.png");
    //font = LoadFont("fonts/yourfont.ttf"); // Load font if any custom font
      PlayMusicStream(theme);
    // startButton = Button{"images/start.png", {955, 280}, 0.8};
    // aboutButton = Button{"images/about.png", {955, 380}, 0.8};
    // exitButton = Button{"images/exit.png", {955, 480}, 0.8};

    initialPosition={0, 700/*screenheight*/- frameRec.height-10};//initial position of the image
 targetPosition={1100/*screenwidth*//2.0f- frameRec.width/4.0f, initialPosition.y};
 standPosition={1100/*screenwidth*//2.0f- frameRec2.width/4.0f,700-frameRec2.height};

    frameRec = {0.0f, 0.0f, (float)broom.width / 6, (float)broom.height}; // assuming 6 frames horizontally
    frameRec2 = {0.0f, 0.0f, (float)stand.width, (float)stand.height};
    textArea = {850, 670, 0, 100};
}


void Menu::UpdateButtons(bool &exit, GameState &currentState) {
    Vector2 mousePosition = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (startButton.isPressed(mousePosition, mousePressed)) {
        currentState = MAP;
    }
    if (aboutButton.isPressed(mousePosition, mousePressed)) {
        // Show "About" information
    }
    if (exitButton.isPressed(mousePosition, mousePressed)) {
        exit = true;
    }
}

Menu::Menu()  : startButton("images/startButton.png", {600, 400}, 1.0f),  // Pass the correct parameters to the Button constructor
      exitButton("images/exitButton.png", {600, 500}, 1.0f),   frameCounter(0), currentFrame(0), frameSpeed(5), delayTime(1.5f),
      timeElapsed(0.0f), typingSpeed(0.05f), isBroom(true), isReachedTarget(false),
      messageIndex(0), charIndex(0), lineHeight(30), timePassed(0.0f)
     {
    // messages[0] = "Hello There!!! Ready to conquer?";
    // messages[1] = "I hope you are ready.But hey don't hit (START) just yet!";
    // messages[2] = "Master the game by first mastering the rules.";
    // messages[3] = "Take a moment to check about page -it could save you from a few extra lives";
    // messages[4] = "Good luck with the Game.";
    // messages[5]=" ";
}

void Menu::UpdateAnimation() {
    UpdateMusicStream(theme);
    if (isBroom && initialPosition.x < targetPosition.x) {
        frameCounter++;
        if (frameCounter >= (60 / frameSpeed)) {
            frameCounter = 0;
            currentFrame++;
            if (currentFrame >= 6) currentFrame = 0;
            frameRec.x = (float)currentFrame * frameRec.width;
        }
        initialPosition.x += 1.0f;
    }
    if (!isReachedTarget && initialPosition.x >= targetPosition.x) {
        isReachedTarget = true;
    }
    if (isReachedTarget && isBroom)
{
   timeElapsed+=GetFrameTime();
   if(timeElapsed>=delayTime)
   {
      isBroom= false;
}
}
}

void Menu::UpdateTypingEffect() {
    if (IsKeyPressed(KEY_SPACE) && messageIndex < 5) {
        messageIndex++;
        charIndex = 0;
        timePassed = 0.0f;
    }

    timePassed += GetFrameTime();
    if (timePassed >= typingSpeed && charIndex < static_cast<int>(strlen(messages[messageIndex]))) {
        charIndex++;
        timePassed = 0.0f;
    }
}

void Menu::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    if (isBroom) {
        DrawTextureRec(broom, frameRec, initialPosition, WHITE);
    } else {
        DrawTextureRec(stand, frameRec, targetPosition, WHITE);
    }

    int currentCharIndex = 0;
    int line = 0;
    for (int i = 0; i < charIndex && line < MAX_LINES; i++) {
        if (currentCharIndex >= MAX_CHARACTERS_PER_LINE || messages[messageIndex][i] == '\n') {
            line++;
            currentCharIndex = 0;
        }
        if (line < MAX_LINES) {
           DrawTextEx(font,TextFormat("%c", messages[messageIndex][i]), (Vector2){textArea.x + currentCharIndex * 16, 
                         textArea.y + line * lineHeight},25,2,WHITE);
                currentCharIndex++ ;
        }
    }
    if (messageIndex < 5 && charIndex == static_cast<int>( strlen(messages[messageIndex]))) {
        DrawText("Press SPACE for next message", 1000, 770, 20, WHITE);
    }

    startButton.Draw();
    aboutButton.Draw();
    exitButton.Draw();
}

void Menu::Unload() {
    UnloadTexture(background);
    UnloadTexture(broom);
    UnloadTexture(stand);
    UnloadMusicStream(theme);
    CloseAudioDevice();
}

