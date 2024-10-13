// #include "collectibles.h"
// #include "raylib.h"
// #include "globals.h"
// #include "character.h"
// #include <iostream>

// extern Character hp; // Ensure hp is declared as extern if used here

// Collectibles::Collectibles() : texture({0}), speed(0.005f), snitch_timer(0.0f)
// {
//     std::cout << "Collectibles constructor called";
//     position = GenerateRandomPosition();
// }

// Texture2D Collectibles::LoadTexture(const char *filePath)
// {
//     Texture2D texture;
//     Image img;
//     img = LoadImage(filePath);
//     ImageResize(&img, 30, 30);
//     texture = LoadTextureFromImage(img);
//     if (texture.id == 0)
//     {
//         TraceLog(LOG_ERROR, "Texture not loaded");
//     }
//     else
//     {
//         TraceLog(LOG_INFO, "Texture loaded!!!");
//     }
//     return texture;
// }

// void Collectibles::Update()
// {
//     snitch_timer += GetFrameTime(); // Update the snitch_timer with the frame time

//     if (snitch_timer >= 10.0f) // If 10 seconds have passed
//     {
//         position = GenerateRandomPosition(); // Generate a new random position
//         snitch_timer = 0.0f;                 // Reset the snitch_timer
//     }

//     // Check for collision with the character
//     if (CheckCollisionRecs({position.x * cellSize, position.y * cellSize, 30, 30}, Rectangle{hp.x, hp.y, 100, 100}))
//     {
//         std::cout << "Collision detected" << std::endl;
//         CollectibleCount++;
//         position = GenerateRandomPosition(); // Generate a new random position on collision
//         snitch_timer = 0.0f;                 // Reset the snitch_timer
//     }
// }

// Collectibles::~Collectibles()
// {
//     std::cout << "Collectibles destructor called" << std::endl;
//     UnloadTexture(texture);
// }

// void Collectibles::Draw(Texture2D texture)
// {
//     DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
//     DrawText(("Collectible Count: " + std::to_string(CollectibleCount)).c_str(), 100, 200, 20, DARKGRAY);
// }

// Vector2 Collectibles::GenerateRandomPosition()
// {
//     float x = GetRandomValue(0, cellCountX - 1);
//     float y = GetRandomValue(0, cellCountY - 1);
//     return Vector2{x, y};
// }