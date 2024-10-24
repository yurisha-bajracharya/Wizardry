// collectibles.h
#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H

extern int CollectibleCount; // declaring CollectibleCount as an external variable

class Collectibles
{
public:
    Collectibles();
    Texture2D LoadTexture(const char *fileName);
    ~Collectibles();
    void Draw(Texture2D texture);
    void DrawBludgers(Texture2D texture);
    Vector2 GenerateRandomPosition();
    void Update();
    void UpdateBludgers();

private:
    Texture2D texture;
    Texture2D bludger_texture;
    Vector2 snitch_position;
    Vector2 bludger_positions[4];
    Vector2 bludger_velocities[4];
    float bludger_speed;
    float speed;
    float snitch_timer;
};

#endif // COLLECTIBLES_H