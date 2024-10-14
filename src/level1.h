#ifndef LEVEL1_H
#define LEVEL1_H

#include "raylib.h"

void UpdateLevel1();
void DrawLevel1();
void DrawCollectible(Texture2D texture);
void InitLevel1();
void UnloadLevel1();
void DrawBludgers(Texture2D bludgerTexture);

#endif // LEVEL1_H