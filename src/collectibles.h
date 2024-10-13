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
    void Draw(Texture2D texture1, Texture2D texture2);
    Vector2 GenerateRandomPosition();
    void Update();

    private:
    Vector2 position1, position2;
    Texture2D texture1, texture2;
    float speed;
};

#endif // COLLECTIBLES_H