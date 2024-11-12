// collectibles.h
#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H
#include "C:\raylib\raylib\src\raylib.h"

extern int CollectibleCount; // declaring CollectibleCount as an external variable

class Collectibles
{
public:
    Collectibles();
    Texture2D LoadTexture(const char *fileName);
    ~Collectibles();
    void Draw(Texture2D texture);
    void DrawBludgers(int i, Texture2D texture);
    Vector2 GenerateRandomPosition();
    void Update();
    void UpdateBludgers(int i);

private:
    Texture2D texture;
    Texture2D bludger_texture;
    Vector2 snitch_position;
    Vector2 bludger_positions[3];
    Vector2 bludger_velocities[3];
    float speed;
    float snitch_timer;
};

#endif // COLLECTIBLES_H