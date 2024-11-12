// class Character
#ifndef CHARACTER_H
#define CHARACTER_H

#include "C:\raylib\raylib\src\raylib.h"

class Character
{
public:
    float x, y;
    Texture2D texture;
    Character();
    ~Character();
    void Draw(Texture2D texture);
    void Update();
    float hp_pause_timer;
    bool isHpPaused;
};

#endif // CHARACTER_H