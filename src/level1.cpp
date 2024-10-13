#include "raylib.h"
#include "level1.h"
#include <iostream>
#include "collectibles.h"
#include "character.h"
#include "globals.h"
#include <cstdio> // Add this line to include the header file that declares the FormatText function
using namespace std;

const int screenWidth = 1400;
const int screenHeight = 900;
int cellSize = 50;
const int cellCountX = screenWidth / cellSize;
const int cellCountY = screenHeight / cellSize;
int CollectibleCount = 0;

Character hp;

// loading the background music
Sound level1Music;

Collectibles::Collectibles() : texture1({0}), texture2({0}), speed(0.005f)
{
    cout << "Collectibles constructor called";
    position1 = GenerateRandomPosition();
    position2 = GenerateRandomPosition();
}

Texture2D Collectibles::LoadTexture(const char *filePath)
{
    Texture2D texture;
    Image img;
    img = LoadImage(filePath);
    ImageResize(&img, 90, 90);
    texture = LoadTextureFromImage(img);
    if (texture.id == 0)
    {
        TraceLog(LOG_ERROR, "Texture not loaded");
    }
    else
    {
        TraceLog(LOG_INFO, "Texture loaded!!!");
    }
    return texture;
}

void Collectibles::Update()
{
    float frameTime = GetFrameTime(); // Get time between frames for smooth movement

    // Move collectibles horizontally only by a smaller value
    position1.x += speed * frameTime * 100.0f; // Multiply by 100 to get a reasonable speed
    position2.x += speed * frameTime * 100.0f;

    // Reset collectible position if it moves out of the screen
    if (position1.x > screenWidth) // Directly compare to screen width
    {
        position1 = GenerateRandomPosition();
    }
    if (position2.x > screenWidth)
    {
        position2 = GenerateRandomPosition();
    }
}

Collectibles::~Collectibles()
{
    cout << "Collectibles destructor called" << endl;
    UnloadTexture(texture1);
    UnloadTexture(texture2);
};

void Collectibles::Draw(Texture2D texture1, Texture2D texture2)
{
    DrawTexture(texture1, position1.x * cellSize, position1.y * cellSize, WHITE);
    DrawTexture(texture2, position2.x * cellSize, position2.y * cellSize, WHITE); // Multiplying by cellSize converts grid coordinates to pixel coordinates for rendering.
    DrawText(("Collectible Count: " + std::to_string(CollectibleCount)).c_str(), 100, 200, 20, DARKGRAY);
    if (CheckCollisionRecs({position1.x * cellSize, position1.y * cellSize, 30, 30}, Rectangle{hp.x, hp.y, 100, 100}))
    {
        std::cout << "Collision detected" << std::endl;
        CollectibleCount++;
        position1 = GenerateRandomPosition();
    }
    if (CheckCollisionRecs({position2.x * cellSize, position2.y * cellSize, 30, 30}, {hp.x, hp.y, 100, 100}))
    {
        std::cout << "Collision detected" << std::endl;
        CollectibleCount++;
        position2 = GenerateRandomPosition();
    }
}

Vector2 Collectibles::GenerateRandomPosition()
{
    float x = GetRandomValue(0, cellCountX - 1);
    float y = GetRandomValue(0, cellCountY - 1);
    return Vector2{x, y};
}

Character::Character()
{
    x = 0;
    y = 0;
}
Character::~Character()
{
}
void Character::Draw(Texture2D texture)
{
    DrawTexture(texture, x, y, WHITE);
}
void Character::Update()
{
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        x += 1;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        x -= 1;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        y -= 1;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        y += 1;
    }

    // FOR faster speed of the character while clicking the keys along with the shift key
    if ((IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_RIGHT_SHIFT)) || (IsKeyDown(KEY_D) && IsKeyDown(KEY_RIGHT_SHIFT)))
    {
        x += 3;
    }
    if ((IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT_SHIFT)) || (IsKeyDown(KEY_A) && IsKeyDown(KEY_RIGHT_SHIFT)))
    {
        x -= 3;
    }
    if ((IsKeyDown(KEY_UP) && IsKeyDown(KEY_RIGHT_SHIFT)) || (IsKeyDown(KEY_W) && IsKeyDown(KEY_RIGHT_SHIFT)))
    {
        y -= 3;
    }
    if ((IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT_SHIFT)) || (IsKeyDown(KEY_S) && IsKeyDown(KEY_RIGHT_SHIFT)))
    {
        y += 3;
    }
}

void UpdateLevel1()
{
    // cout << "UpdateLevel1 called";
    hp.Update();
    collectible.Update();
}

void DrawLevel1(Texture2D character)
{
    DrawText("Level 1 - Collect the valuable items!", 100, 100, 20, DARKGRAY);
    // cout << "DrawLevel1 called";
    hp.Draw(character);
}

// function to initialize level1
void InitLevel1()
{
    if (!IsAudioDeviceReady())
    {
        InitAudioDevice();
    }
    level1Music = LoadSound("./audio/level1.mp3");
    PlaySound(level1Music);
}

void UnloadLevel1()
{
    UnloadSound(level1Music);
    if (IsAudioDeviceReady())
    {
        CloseAudioDevice();
    }
}