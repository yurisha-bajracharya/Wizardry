#include "raylib.h"
#include "level1.h"
#include <iostream>
#include "collectibles.h"
#include "character.h"
#include "globals.h"
#include <cstdio>
#include <cmath>
using namespace std;

const int screenWidth = 1400;
const int screenHeight = 900;
const int cellSize = 50; // Ensure cellSize is defined as a constant
const int cellCountX = screenWidth / cellSize;
const int cellCountY = screenHeight / cellSize;
int CollectibleCount = 0;

Character hp;
Sound level1Music, hitSound;
Texture2D characterimg;
Texture2D characterimgfrozen;

// Define the dimensions of the bludger and the character
const float bludgerWidth = 15.0f;    // Width of the bludger
const float bludgerHeight = 15.0f;   // Height of the bludger
const float characterWidth = 30.0f;  // Width of the character
const float characterHeight = 30.0f; // Height of the character

Collectibles::Collectibles() : texture{0}, bludger_texture{0}, snitch_position{0, 0}, bludger_positions{{0, 0}}, bludger_velocities{{0, 0}}, bludger_speed{200}, speed{200}, snitch_timer{0.0f}
{
    cout << "Collectibles constructor called";
    snitch_position = GenerateRandomPosition();

    for (int i = 0; i < 1; i++)
    {
        bludger_positions[i].x = GetRandomValue(0, GetScreenWidth() - 30);
        bludger_positions[i].y = -30;
        bludger_velocities[i].y = GetRandomValue(2, 5);
    };
}

Texture2D Collectibles::LoadTexture(const char *filePath)
{
    Texture2D texture;
    Image img;
    img = LoadImage(filePath);
    ImageResize(&img, 60, 60);
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
    snitch_timer += GetFrameTime(); // Update the timer with the frame time

    if (snitch_timer >= 4.0f)
    {
        snitch_position = GenerateRandomPosition(); // Generate a new random position
        snitch_timer = 0.0f;
    }

    // Check for collision with the character
    if (CheckCollisionRecs({snitch_position.x * cellSize, snitch_position.y * cellSize, 30, 30}, Rectangle{hp.x, hp.y, 100, 100}))
    {
        std::cout << "Collision detected" << std::endl;
        Sound chimeMusic = LoadSound("./audio/chime-sound.mp3");
        PlaySound(chimeMusic);
        CollectibleCount++;
        snitch_position = GenerateRandomPosition(); // Generate a new random position on collision
        snitch_timer = 0.0f;                        // Reset the timer
    }
}

void Collectibles::UpdateBludgers()
{
    cout << "UpdateBludgers called" << endl;

    for (int i = 0; i < 1; i++)
    {
        cout << "reachedd" << endl;
        bludger_velocities[i].y += 0.05f;

        bludger_positions[i].y += bludger_velocities[i].y * GetFrameTime() * bludger_speed;
        cout << "Bludger Y-Position: " << bludger_positions[i].y << endl;

        if (CheckCollisionCircles(Vector2{bludger_positions[i].x + bludgerRadius, bludger_positions[i].y + bludgerRadius}, bludgerRadius, Vector2{hp.x + characterRadius, hp.y + characterRadius}, characterRadius)) // syntax: CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2)
        {
            PlaySound(hitSound);
            hp.isHpPaused = true;
            hp.hp_pause_timer = 0.0f;
        }

        // Reset bludger position if it moves out of the screen
        if (bludger_positions[i].y > GetScreenHeight())
        {
            do
            {
                bludger_positions[i].x = GetRandomValue(0, GetScreenWidth() - 30);
                bludger_positions[i].y = 0; // Reset to the top of the screen
            } while (CheckCollisionRecs(Rectangle{bludger_positions[i].x, bludger_positions[i].y, bludgerWidth, bludgerHeight}, Rectangle{hp.x, hp.y, characterWidth, characterHeight}));
            bludger_velocities[i].y = 0.0f; // Reset velocity
        }

        if (CheckCollisionRecs(Rectangle{bludger_positions[i].x, bludger_positions[i].y, bludgerWidth, bludgerHeight}, Rectangle{hp.x, hp.y, characterWidth, characterHeight}))
        {
            cout << "Harry Position: (" << hp.x << ", " << hp.y << ")" << endl;
            cout << "Bludger Position: (" << bludger_positions[i].x << ", " << bludger_positions[i].y << ")" << endl;
            PlaySound(hitSound);
            hp.isHpPaused = true;
            hp.hp_pause_timer = 0.0f;
        }
    }
}

Collectibles::~Collectibles()
{
    cout << "Collectibles destructor called" << endl;
    UnloadTexture(texture);
    UnloadTexture(bludger_texture);
};

void Collectibles::Draw(Texture2D texture)
{
    DrawTexture(texture, snitch_position.x * cellSize, snitch_position.y * cellSize, WHITE);
    DrawText(("Snitch Count: " + std::to_string(CollectibleCount)).c_str(), 590, 100, 30, GOLD);
}

void Collectibles::DrawBludgers(Texture2D bludgerTexture)
{
    for (int i = 0; i < 1; i++)
    {
        DrawTexture(bludgerTexture, bludger_positions[i].x, bludger_positions[i].y, WHITE);
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
    x = 680;
    y = 445;
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
    if (!hp.isHpPaused)
    {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            x += 5;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            x -= 5;
        }
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            y -= 5;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            y += 5;
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

    else if (hp.isHpPaused)
    {
        hp.hp_pause_timer += GetFrameTime();
        if (hp.hp_pause_timer >= 2.0f)
        {
            hp.isHpPaused = false;
            hp.hp_pause_timer = 0.0f;
        }
    }
}

void UpdateLevel1()
{
    hp.Update();
    collectible.Update();
    collectible.UpdateBludgers();
}

void DrawLevel1()
{
    if (!hp.isHpPaused)
    {
        hp.Draw(characterimg);
    }
    else
    {
        hp.Draw(characterimgfrozen);
    }
}

void DrawCollectible(Texture2D texture)
{
    collectible.Draw(texture);
}

void DrawBludgers(Texture2D bludgerTexture)
{
    collectible.DrawBludgers(bludgerTexture);
}

void InitLevel1()
{
    if (!IsAudioDeviceReady())
    {
        InitAudioDevice();
    }
    level1Music = LoadSound("./audio/level1.mp3");
    PlaySound(level1Music);
    hitSound = LoadSound("./audio/hit.mp3");
    hp.isHpPaused = false;

    Image charimg = LoadImage("./images/hpright.png");
    Image charimgfrozen = LoadImage("./images/hp-frozen.png");
    ImageResize(&charimg, 120, 120);
    ImageResize(&charimgfrozen, 120, 120);
    characterimg = LoadTextureFromImage(charimg);
    characterimgfrozen = LoadTextureFromImage(charimgfrozen);

    UnloadImage(charimg);
    UnloadImage(charimgfrozen);
}

void UnloadLevel1()
{
    UnloadSound(level1Music);
    UnloadTexture(characterimg);
    UnloadTexture(characterimgfrozen);
    if (IsAudioDeviceReady())
    {
        CloseAudioDevice();
    }
}