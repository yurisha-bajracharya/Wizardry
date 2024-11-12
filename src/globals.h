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

// enum GameState
// {
//     MENU = 0,
//     MAP,
//     LEVEL1,
//     LEVEL2,
//     LEVEL3,
//     GAMEOVER,
//     PAUSE1,
//     PAUSE2
// };

// extern GameState currentState;

#endif // GLOBALS_H

