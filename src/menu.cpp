#include "C:\raylib\raylib\src\raylib.h"
#include "menu.h"
#include "string.h"

#define MAX_LINES 6
#define MAX_CHARACTERS_PER_LINE 35

// Texture objects
Texture2D backgroundm;
Texture2D broom;
Texture2D stand;
Music musicm;

// Variables
bool exit1 = false;
float delayTime = 1.5f;
float timeElapsed = 0.0f;
Vector2 initialPosition;
Vector2 targetPosition;
Vector2 standPosition;

bool isBroom = true;
bool isReachedTarget = false;
bool timeForText = false;

// Text messages
const char *messages[] = {
    "Hello There!!! Ready to conquer?",
    "I hope you are ready. But hey don't hit (START) just yet!",
    "Master the game by first mastering the rules.",
    "Take a moment to check the about page - it could save you from a few extra lives",
    "Good luck with the Game.",
    " "};

Font font = GetFontDefault();
int messageIndex = 0;
int charIndex = 0;
float typingSpeed = 0.05f;
float timePassed = 0.0f;
int totalMessages = sizeof(messages) / sizeof(messages[0]);

Rectangle textArea = {100, 370, 1080, 200};
int lineHeight = 40;

void InitMenu()
{
    // Load assets
    backgroundm = LoadTexture("./images/ok.png");
    broom = LoadTexture("./images/cute.png");
    stand = LoadTexture("./images/stand.png");
    musicm = LoadMusicStream("./Audio/main.mp3");
    PlayMusicStream(musicm);

    // Initialize positions based on loaded textures
    initialPosition = (Vector2){0, 500};
    // Define the right offset
    float offsetRight = 200.0f; // Adjust this value as needed

    // Update positions with the offset
    targetPosition = (Vector2){1280 / 2.0f - broom.width / 2.0f + offsetRight, initialPosition.y};
    standPosition = (Vector2){1280 / 2.0f - stand.width / 2.0f + offsetRight, 700 - static_cast<float>(stand.height)};
}

void UpdateMenu()
{
    UpdateMusicStream(musicm);

    // Broom movement logic
    if (isBroom && initialPosition.x < targetPosition.x)
    {
        initialPosition.x += 200.0f * GetFrameTime();
    }

    if (initialPosition.x >= targetPosition.x && !isReachedTarget)
    {
        isReachedTarget = true;
        timeElapsed += GetFrameTime();

        if (timeElapsed >= delayTime)
        {
            isBroom = false;
            timeForText = true;
        }
    }

    // Typing effect logic for messages
    if (!isBroom && timeForText)
    {
        if (IsKeyPressed(KEY_SPACE) && messageIndex < totalMessages - 1)
        {
            messageIndex++;
            charIndex = 0;
            timePassed = 0.0f;
        }

        timePassed += GetFrameTime();
        if (timePassed >= typingSpeed && charIndex < static_cast<int>(strlen(messages[messageIndex])))
        {
            charIndex++;
            timePassed = 0.0f;
        }
    }
}

void DrawMenu()
{
    ClearBackground(WHITE);
    DrawTexture(backgroundm, 0, 0, WHITE);

    // Draw broom or stand based on state
    if (isBroom)
    {
        DrawTexture(broom, initialPosition.x, initialPosition.y, WHITE);
    }
    else
    {
        DrawTexture(stand, standPosition.x, standPosition.y, WHITE);
    }

    // Draw text with word wrapping and typing effect
    int currentCharIndex = 0;
    int line = 0;
    for (int i = 0; i < charIndex && line < MAX_LINES; i++)
    {
        if (currentCharIndex >= MAX_CHARACTERS_PER_LINE || messages[messageIndex][i] == '\n')
        {
            line++;
            currentCharIndex = 0;
        }

        if (line < MAX_LINES)
        {
            DrawTextEx(font, TextFormat("%c", messages[messageIndex][i]),
                       (Vector2){textArea.x + currentCharIndex * 18, textArea.y + line * lineHeight}, 30, 2, DARKGRAY);
            currentCharIndex++;
        }
    }

    // Instruction to proceed to the next message
    if (timeForText && messageIndex < totalMessages - 1 && charIndex == static_cast<int>(strlen(messages[messageIndex])))
    {
        DrawText("Press SPACE for next message", 900, 650, 20, LIGHTGRAY);
    }
}