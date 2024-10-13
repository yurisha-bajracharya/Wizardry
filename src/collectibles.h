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
    Vector2 GenerateRandomPosition();
    void Update();

private:
    Texture2D texture;
    Vector2 snitch_position;
    float speed;
    float snitch_timer;
};

#endif // COLLECTIBLES_H