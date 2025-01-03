#include "C:\raylib\raylib\src\raylib.h"
#include <iostream>
#include "level3.h"
#include <vector>
#include <algorithm>
#include "globals.h"
#include <random>
#include <string.h>
#include <cstring>
#include "button.h"

#define MAX_LINES 6                // Maximum number of lines in the area
#define MAX_CHARACTERS_PER_LINE 35 // Maximum characters per line before wrapping

using namespace std;

// Game assets
Music voldeEntry;
Sound complete;
Sound voldeHappy;
Sound voldeSad;
Texture2D level3bg;
Texture2D voldeBaba;
Texture2D lovies;
Texture2D riText;
Button hintButton;
Texture2D hintB;
Color OLIVE_GREEN = {107, 142, 35, 255};

// Constants for popup
const float popupDuration = 2.0f; // Popup duration in seconds

// Variables for popup state
bool showPopup = false;
float popupTimer = 0.0f;

// Positions and animation variables
Vector2 firstPosition;
Vector2 finalPosition;
int frameCount1 = 6;
Rectangle frameRec1;
int currentframe1 = 0;
int frameCounter1 = 0;
int frameSpeed1 = 5;
bool reachedTarget = false;
bool riddleComplete = false;
bool isWon = false;
// bool nohint = false;
//  Voldemort dialog variables
const char *prabachan[] = {
    "HAHAHAHA, You're almost there, but until you solve this, you haven't   won.",
    "Let's see if your feeble mind can   unravel this riddle, shall we?",
    "You think you can solve this?",
    "Prove me wrong, and perhaps I'll   allow you the luxury of a score.",
    "Now, ready yourself.",
    " "};

int messageIndex1 = 0;
int charIndex1 = 0;
float typingSpeed1 = 0.03f;
float timePassed1 = 0.0f;
int totalMessages1 = sizeof(prabachan) / sizeof(prabachan[0]);
Rectangle textArea1 = {350, 360, 0, 50};
int lineHeight1 = 35;
Font font1 = fontBold;

// Riddle variables
struct Riddle
{
    string question;
    string answer;
    string hint;
};
vector<Riddle> riddles = {
    {"I am not alive, but I can grow;\n \nI don't have lungs, but I need air;\n\n I don't have a mouth, but water kills me.\n\n What am I?", "FIRE", "Think about something that comes \n\nfrom a dragon."},
    {"What can only be seen once\n\n it's broken?", "PROMISE", "Dumbledore warned Harry about this in \n\n\nThe Half-Blood Prince."},
    {"I open at the close.\n\n What am I?", "THE SNITCH", "Quidditch players will know this!"},
    {"I have a beginning, but no end.\n\n I grow with age, but shrink with wisdom. \n\n What am I?", "TIME", "Professor Trelawney talks about this\n\n constantly."},
    {"What belongs to you,\n\n but others use it more than you do?", "NAME", "Think about how people address you."},
    {"I am always hungry, I must always be fed.\n \n The finger I touch will soon turn red. What am I?", "FIRE", "It burns and requires fuel to survive."},
    {"I am the one who will never lie,I never speak, \n\nbut I tell the truth,With my face, you always decide,\n\n What I show is always the proof.What am I?", "MIRROR", "Think about the Mirror of Erised\n\n and how it shows what the heart desires."},
    {"I can be cracked, I can be made,\n\n I can be told, I can be played.What am I?", "JOKE", "A certain professor in Harry Potter and\n\n the Prisoner of Azkaban would love this one."},
    {"What is invisible and makes the loudest sound,\n\n But no one can see it or touch it?", "MAGIC", "Wizards and witches use it daily,\n\n but you can't see it."},
    {"The more you have of me,The less you see.\n\nWhat am I?", "DARKNESS", "Think about the Forbidden Forest at night."},
    {"I have a face, but no eyes,I have hands, \n\nbut no arms,I have a body, but no legs,\n\nWhat am I?", "CLOCK", "The timepiece that governs much of \n\nlife at Hogwarts."},
    {"I have many faces,But no eyes to see.\n\nI change my form often,What could I be?", "COIN", "Think about the Galleons in the wizarding\n\n world, which have two sides."}};
vector<Riddle> selectedRiddles;
int currentRiddle = 0;
string playerInput = "";
bool showResult = false;
bool isCorrect = false;
bool hintShown = false;
int score = 0;

// New variable to manage game phases
enum GamePhase
{
    VOLDEMORT_MESSAGES,
    RIDDLE_QUIZ
};
GamePhase gamePhase = VOLDEMORT_MESSAGES;

// Utility function for lowercase conversion
string toLower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
// hints
void extraHint()
{
    coinsCollected = coinsCollected / 3;
}

/*********************RIDDLE SCREEN************************** */
void drawRiddleScreen(const Riddle &riddle, const string &playerInput, int score)
{

    DrawTextEx(fontBold, ("Riddle: " + riddle.question).c_str(), (Vector2){350, 290}, 35, 2.5, WHITE);
    DrawText(("Score: " + to_string(score)).c_str(), 70, 150, 25, GREEN); // Display score

    // HINT
    if (hintShown)
    {
        DrawTextEx(medium, ("Hint: " + riddle.hint).c_str(), (Vector2){340, 440}, 30, 2.5, YELLOW);
    }
    DrawText("Type your answer:", 620, 570, 27, LIGHTGRAY);
    DrawTextEx(fontNormal, ("Answer: " + playerInput).c_str(), Vector2{620, 605}, 30, 2.5, WHITE); // Display real-time input
}

void initNewLevel3()
{

    level3bg = LoadTexture("images/riddle1.png");
    voldeBaba = LoadTexture("images/voldemort.png");
    lovies = LoadTexture("images/lovies.png");
    riText = LoadTexture("images/dd.png");
    voldeEntry = LoadMusicStream("Audio/volde.mp3");
    voldeHappy = LoadSound("Audio/voldeHappy.mp3");
    voldeSad = LoadSound("Audio/voldeSad.mp3");
    complete = LoadSound("Audio/forRiddle.mp3");
    PlayMusicStream(voldeEntry);

    PlayMusicStream(voldeEntry);

    // Initialize hintButton
    hintButton.SetPosition(12, 20);
    hintButton.scale = 1.0f;
    frameRec1 = {0.0f, 0.0f, static_cast<float>(voldeBaba.width), static_cast<float>(voldeBaba.height)};
    firstPosition = {0, 0};
    finalPosition = {firstPosition.x, 700 - frameRec1.height};
    frameCount1 = 6;
    currentframe1 = 0;
    frameCounter1 = 0;
    frameSpeed1 = 5;
    reachedTarget = false;
    // nohint = false;
    hintShown = false;

    // Reset Voldemort dialog variables
    messageIndex1 = 0;
    charIndex1 = 0;
    timePassed1 = 0.0f;
    gamePhase = VOLDEMORT_MESSAGES;

    // Shuffle and select riddles
    random_device rd;
    mt19937 g(rd());
    shuffle(riddles.begin(), riddles.end(), g);
    selectedRiddles.assign(riddles.begin(), riddles.begin() + 3);

    // Reset riddle variables
    currentRiddle = 0;
    playerInput.clear();
    showResult = false;
    isCorrect = false;
    hintShown = false;
    score = 0;

    // Reset win/loss flags
    isWon = false;
    riddleComplete = false;
}

void updateLevel3()
{
    static bool initialized = false; // Static variable to track initialization
    if (!initialized)
    {
        // InitAudioDevice();
        level3bg = LoadTexture("images/riddle1.png");
        voldeBaba = LoadTexture("images/voldemort.png");
        hintB = LoadTexture("images/hint.png");
        lovies = LoadTexture("images/lovies.png");
        voldeEntry = LoadMusicStream("Audio/volde.mp3");
        voldeHappy = LoadSound("Audio/voldeHappy.mp3");
        voldeSad = LoadSound("Audio/voldeSad.mp3");
        complete = LoadSound("Audio/forRiddle.mp3");
        riText = LoadTexture("images/dd.png");
        PlayMusicStream(voldeEntry);

        frameRec1 = {0.0f, 0.0f, static_cast<float>(voldeBaba.width), static_cast<float>(voldeBaba.height)};

        firstPosition = {0, 0};
        finalPosition = {firstPosition.x, 700 - frameRec1.height};

        // Shuffle and select riddles
        random_device rd;                                             // Seed for random generator
        mt19937 g(rd());                                              // Random number generator
        shuffle(riddles.begin(), riddles.end(), g);                   // Shuffle the riddles
        selectedRiddles.assign(riddles.begin(), riddles.begin() + 3); // Select the first 3 shuffled riddles

        initialized = true;
    }

    UpdateMusicStream(voldeEntry);
    /*****************************VOLDEBABA KO ENTRY*****************************/
    if (firstPosition.y < finalPosition.y)
    {
        frameCounter1++;
        if (frameCounter1 >= (60 / frameSpeed1))
        {
            frameCounter1 = 0;
            currentframe1++;
            if (currentframe1 >= frameCount1)
                currentframe1 = 0;
            frameRec1.y = static_cast<float>(currentframe1) * frameRec1.height;
        }
        firstPosition.y += 1.0f;
    }
    if (firstPosition.y >= finalPosition.y)
    {
        reachedTarget = true;
    }

    // /*************************** VOLDEBABA KO PRABACHAN**********************************/
    if (reachedTarget && gamePhase == VOLDEMORT_MESSAGES)
    {
        if (IsKeyPressed(KEY_RIGHT) && messageIndex1 < totalMessages1 - 1)
        {
            messageIndex1++;
            charIndex1 = 0;
            timePassed1 = 0.0f;
        }

        timePassed1 += GetFrameTime();
        if (timePassed1 >= typingSpeed1 && charIndex1 < static_cast<int>(strlen(prabachan[messageIndex1])))
        {
            charIndex1++;
            timePassed1 = 0.0f;
        }

        /*************************** VOLDEBABA KO questions**********************************/
        if (messageIndex1 >= totalMessages1 - 1 && charIndex1 >= static_cast<int>(strlen(prabachan[messageIndex1])))
        {
            gamePhase = RIDDLE_QUIZ;
            StopMusicStream(voldeEntry); // to stop music cause it's irritating
        }
    }

    /***********************************ALL ABOUT RIDDLE************************** */
    int key = GetKeyPressed();
    if (key >= 32 && key <= 125)
    {
        playerInput += static_cast<char>(key);
    }
    else if (key == KEY_BACKSPACE && !playerInput.empty())
    {
        playerInput.pop_back();
    }

    // FOR SUBMITTING
    if (IsKeyPressed(KEY_ENTER))
    {
        if (toLower(playerInput) == toLower(selectedRiddles[currentRiddle].answer))
        { // convert both to lowercase

            score++;
            isCorrect = true;
            PlaySound(voldeSad);
        }
        else
        {
            isCorrect = false;
            PlaySound(voldeHappy);
        }
        showResult = true;
    }
    /*************************FOR HINT********************** */
    Vector2 mousePosition = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    {
        if (hintButton.isPressed(mousePosition, mousePressed, hintButton.position, hintButton.scale, hintB.width, hintB.height))
        // {
        //     if (coinsCollected > 0)
        //     {
        //         hintShown = true;
        //     }
        //     else
        //     {
        //       //  nohint = true;
        //     }
        // }
        {

            if (coinsCollected <= 0)
            {
                // Trigger popup if not enough coins
                showPopup = true;
                popupTimer = popupDuration;
            }
            else
            {
                // Show hint logic
                hintShown = true;
            }
        }

        // Update popup timer
        if (showPopup)
        {
            popupTimer -= GetFrameTime();
            if (popupTimer <= 0.0f)
            {
                showPopup = false; // Hide the popup after the duration
            }
        }
    }
}

void drawLevel3()
{

    DrawTexture(level3bg, 0, 0, WHITE);

    DrawTextureRec(voldeBaba, frameRec1, firstPosition, WHITE);
    DrawTexture(lovies, 890, 410, WHITE);
    DrawTexture(riText, 585, 105, WHITE);
    hintButton.Draw(hintB, hintButton.scale);
    // fOR TYPING TEXT EFFECT.....................
    int currentcharIndex1 = 0;
    int line = 0;
    for (int i = 0; i < charIndex1 && line < MAX_LINES; i++)
    {
        if (currentcharIndex1 >= MAX_CHARACTERS_PER_LINE || prabachan[messageIndex1][i] == '\n')
        {
            line++;
            currentcharIndex1 = 0;
        }
        if (line < MAX_LINES)
        {
            DrawTextEx(font1, TextFormat("%c", prabachan[messageIndex1][i]),
                       (Vector2){textArea1.x + currentcharIndex1 * 16, textArea1.y + line * lineHeight1},
                       25, 2, WHITE);
            currentcharIndex1++;
        }
    }

    if (messageIndex1 < totalMessages1 - 1 && charIndex1 == static_cast<int>(strlen(prabachan[messageIndex1])))
    {
        DrawText("Press RIGHT(>)KEY for next message", 300, 680, 20, WHITE);
    }
    /****************************RIDDLE**************** */
    if (gamePhase == RIDDLE_QUIZ)
    {
        if (showResult)
        {
            if (isCorrect)
            {
                DrawText("Well done, you got it right.\n\n\n How unexpected.", 310, 450, 25, GREEN);
            }
            else
            {

                DrawText(("Oh, how shocking... wrong! \n\n\nThe answer was: " + selectedRiddles[currentRiddle].answer).c_str(), 310, 450, 25, RED);
            }
            if (currentRiddle + 1 < static_cast<int>(selectedRiddles.size()))
            {
                DrawText("Press SPACE for next riddle...", 600, 660, 20, WHITE);
                if (IsKeyPressed(KEY_SPACE))
                {
                    currentRiddle++;
                    showResult = false;
                    playerInput.clear();
                    isCorrect = false;
                    hintShown = false;
                }
            }
            else
            {
                DrawText("Game Over! Press Q to go to next...", 600, 660, 20, WHITE);
                // riddleComplete= true;
            }
            if (score >= 2 && currentRiddle + 1 == static_cast<int>(selectedRiddles.size()) && IsKeyPressed(KEY_Q))
            {
                isWon = true;
                riddleComplete = true;
            }
            if (score < 2 && currentRiddle + 1 == static_cast<int>(selectedRiddles.size()) && IsKeyPressed(KEY_Q))
            {
                isWon = false;
                riddleComplete = true;
            }
        }
        else
        {
            drawRiddleScreen(selectedRiddles[currentRiddle], playerInput, score);
        }
    }

    if (showPopup)
    {
        DrawTextEx(fontBold, "You don't have enough coins to buy hint", (Vector2){68, 21}, 30, 2.5, RED);
    }
}

void UnloadLevel3()
{
    // Unload and reload assets
    UnloadTexture(level3bg);
    UnloadTexture(voldeBaba);
    UnloadTexture(lovies);
    UnloadTexture(riText);
    UnloadMusicStream(voldeEntry);
    UnloadSound(complete);
    UnloadSound(voldeHappy);
    UnloadSound(voldeSad);
}
