#pragma once
#include"raylib.h"
class Button
{
    public:
      Button(const char* imagepath,Vector2 imageposition,float scale);
      ~Button();
      void Draw();
      bool isPressed(Vector2 mousePos, bool mousePressed);
    private:
    Texture texture;
    Vector2 position;


};