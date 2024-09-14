// collectibles.h
#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H

class Collectibles
{
public:
    Vector2 position1, position2;
    Texture2D texture1, texture2;
    Collectibles();
    Texture2D LoadTexture(const char *fileName);
    ~Collectibles();
    void Draw(Texture2D texture1, Texture2D texture2);
    Vector2 GenerateRandomPosition();
};

#endif // COLLECTIBLES_H