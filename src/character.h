// class Character
#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"

class Character
{
public:
    float x, y;
    Texture2D texture;
    Character();
    ~Character();
    void Draw(Texture2D texture);
    void Update();
};

#endif // CHARACTER_H