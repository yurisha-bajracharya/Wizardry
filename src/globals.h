#ifndef GLOBALS_H
#define GLOBALS_H

#include "collectibles.h"
#include "character.h"

extern Collectibles collectible;
extern Character hp;
extern int CollectibleCount;
extern int coinsCollected;
extern bool gameWon;
extern bool gameOver;
extern Font fontBold;
extern Font fontNormal;

void InitFonts();
void UnloadFonts();

#endif // GLOBALS_H

