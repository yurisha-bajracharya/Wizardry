#include "C:\raylib\raylib\src\raylib.h"
#include "level1.h"
#include <iostream>
#include "collectibles.h"
#include "character.h"
#include "globals.h"
#include <cstdio>
#include <cmath>
#include <string>
using namespace std;

const int screenWidth = 1260;
const int screenHeight = 700;
const int cellSize = 50; // Ensure cellSize is defined as a constant
const int cellCountX = screenWidth / cellSize;
const int cellCountY = screenHeight / cellSize;
int CollectibleCount = 0;

Character hp;
Sound level1Music, hitSound, chimeMusic;
Texture2D characterimg;
Texture2D characterimgfrozen;

// Define the dimensions of the bludger and the character
const float bludgerWidth = 60.0f;     // Width of the bludger
const float bludgerHeight = 60.0f;    // Height of the bludger
const float characterWidth = 100.0f;  // Width of the character
const float characterHeight = 100.0f; // Height of the character
const float bludgerRadius = 30.0f;    // Radius of the bludger
Rectangle hpRect, bludgerRect;

float collisionCooldownTimer = 0.0f; // Timer to prevent multiple collisions

Collectibles::Collectibles() : texture{0}, bludger_texture{0}, snitch_position{0, 0}, bludger_positions{{0, 0}, {0, 0}, {0, 0}}, bludger_velocities{{0, 0}, {0, 0}, {0, 0}}, speed{200}, snitch_timer{0.0f}
{
    cout << "Collectibles constructor called";
    snitch_position = GenerateRandomPosition();

    // hpRect = {hp.x, hp.y, characterWidth, characterHeight};

    for (int i = 0; i < 3; i++)
    {
        do
        {
            bludger_positions[i].x = GetRandomValue(30, 1200);
            bludger_positions[i].y = -30; // Start from the top of the screen
        } while (CheckCollisionRecs(Rectangle{bludger_positions[i].x, bludger_positions[i].y, bludgerWidth, bludgerHeight}, hpRect));
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
    if (CheckCollisionCircles({snitch_position.x * cellSize + 30, snitch_position.y * cellSize + 30}, 30, {hp.x + characterWidth / 2, hp.y + characterHeight / 2}, characterWidth / 2))
    {

        PlaySound(chimeMusic);
        CollectibleCount++;
        snitch_position = GenerateRandomPosition(); // Generate a new random position on collision
        snitch_timer = 0.0f;                        // Reset the timer
    }
}

void Collectibles::UpdateBludgers(int i)
{
    // to update the cooldown timer
    if (collisionCooldownTimer > 0.0f)
    {
        collisionCooldownTimer -= GetFrameTime();
    }

    bludger_velocities[i].y += 0.1f;                   // Increase the velocity of the bludger
    bludger_positions[i].y += bludger_velocities[i].y; // Update the position of the bludger

    if (collisionCooldownTimer <= 0.0f)
    {
        if (bludger_positions[i].x < hp.x + characterWidth &&
            bludger_positions[i].x + bludgerWidth > hp.x &&
            bludger_positions[i].y < hp.y + characterHeight &&
            bludger_positions[i].y + bludgerHeight > hp.y)
        {
            cout << "Collision detected" << endl;
            cout << "Harry Position: (" << hp.x << ", " << hp.y << ")" << endl;
            cout << "Bludger Position: (" << bludger_positions[i].x << ", " << bludger_positions[i].y << ")" << "It was bludger no. : " << i << endl;
            PlaySound(hitSound);
            hp.isHpPaused = true;
            hp.hp_pause_timer = 0.0f;
            collisionCooldownTimer = 3.0f;
        }
    }

    // Reset bludger position if it moves out of the screen
    if (bludger_positions[i].y > GetScreenHeight())
    {
        do
        {
            bludger_positions[i].x = GetRandomValue(0, GetScreenWidth() - bludgerWidth);
            bludger_positions[i].y = 0; // Reset to the top of the screen
        } while (CheckCollisionRecs(Rectangle{bludger_positions[i].x, bludger_positions[i].y, bludgerWidth, bludgerHeight}, hpRect));
        bludger_velocities[i].y = 0.0f; // Reset velocity
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
    DrawText(("Snitch Count: " + std::to_string(CollectibleCount)).c_str(), 573, 52, 15, BLACK);
}

void Collectibles::DrawBludgers(int i, Texture2D bludgerTexture)
{

    DrawTexture(bludgerTexture, bludger_positions[i].x, bludger_positions[i].y, WHITE);
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
        // Normal speed
        float speed = 5.0f;

        // If shift key is held down, increase the speed
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        {
            speed = 10.0f; // Adjust this value for desired faster speed
        }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            x += speed;
        }
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            x -= speed;
        }
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {
            y += speed;
        }

        // Ensure character doesn't go out of screen bounds
        if (x < 0)
            x = 0;
        if (x > screenWidth - characterWidth)
            x = screenWidth - characterWidth;
        if (y < 0)
            y = 0;
        if (y > screenHeight - characterHeight)
            y = screenHeight - characterHeight;
    }

    else if (hp.isHpPaused)
    {
        hp.hp_pause_timer += GetFrameTime();
        if (hp.hp_pause_timer >= 3.0f)
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
    // collectible.UpdateBludgers();
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

void InitLevel1()
{
    if (!IsAudioDeviceReady())
    {
        InitAudioDevice();
    }
    level1Music = LoadSound("./audio/level1.mp3");
    PlaySound(level1Music);
    chimeMusic = LoadSound("./audio/chime-sound.mp3");
    hitSound = LoadSound("./audio/hit.mp3");
    hp.isHpPaused = false;

    Image charimg = LoadImage("./images/hpright.png");
    Image charimgfrozen = LoadImage("./images/hp-frozen.png");
    ImageResize(&charimg, 100, 100);
    ImageResize(&charimgfrozen, 100, 100);
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