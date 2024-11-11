#ifndef MENU_H
#define MENU_H

#include<raylib.h>
#include "button.hpp"
#include "globals.h"

class Menu {
private:
    // Menu assets
    Texture2D background;
    Texture2D broom;
    Texture2D stand;
    Music theme;
    //Font font;

    // Buttons
    Button startButton;
    Button aboutButton;
    Button exitButton;
      Font font = GetFontDefault();
    // Animation and text variables
    Vector2 initialPosition;
    Vector2 targetPosition;
    Vector2 standPosition;

       Rectangle frameRec, frameRec2, textArea;
    int frameCounter, currentFrame, frameSpeed;
    float delayTime, timeElapsed, typingSpeed;
    bool isBroom, isReachedTarget;
    const char* messages[6];
    int messageIndex, charIndex, lineHeight;
    float timePassed;

    public:
    Menu();
    void Init();
    void UpdateButtons(bool &exit, GameState &currentState);
    void UpdateAnimation();
    void UpdateTypingEffect();
    void Draw();
    void Unload();
};


#endif // MENU_H