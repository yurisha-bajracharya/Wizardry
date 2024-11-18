#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "credit.h"
#include "globals.h"
#include <cstdlib> // For system()

Texture2D creditbg;
Sound creditaudio;

void InitCredits()
{
        creditaudio = LoadSound("Audio/creditsaudio.mp3");
        PlaySound(creditaudio);
        creditbg = LoadTexture("images/creditsbg.png");
}

void updateCredit()
{
        // credit page
}

void drawCredit()
{
        DrawTexture(creditbg, 0, 0, WHITE);
        DrawTextEx(fontNormal, "GitHub Repo Link:", {20, 20}, 40, 0, ORANGE);
       // DrawTextEx(fontNormal, "CLICK HERE", {20, 60}, 40, 0, ORANGE);

        //Defining the bounding box for the clickable text linking
        Rectangle linkBox = {20, 60, MeasureTextEx(fontBold, "Click Here", 40, 0).x, 40};

        // Check if mouse is hovering over the link
        if (CheckCollisionPointRec(GetMousePosition(), linkBox))
        {
                // Highlight the text on hover
                DrawTextEx(fontNormal, "CLICK HERE", {20, 60}, 40, 0, YELLOW);
        }
        else
        {
                // Default text color when not hovered
                DrawTextEx(fontNormal, "CLICK HERE", {20, 60}, 40, 0, ORANGE);
        }

        // Checking if the mouse is clicked within the bounding box
        if (CheckCollisionPointRec(GetMousePosition(), linkBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
                // Open the URL in the default web browser
                std::system("start https://github.com/yurisha-bajracharya/Wizardry");
        }
}

void UnloadCredits()
{
        UnloadTexture(creditbg);
        UnloadSound(creditaudio);
}