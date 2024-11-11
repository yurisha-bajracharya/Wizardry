#pragma once
#include<raylib.h>
class Button
{
    private:
      Texture2D texture;
      Vector2 position;//In raylib vector2 is a data type representing a 2d point or vector with x and y components
    
    
    public:
    Button(const char *imagepath, Vector2 imagePosition,float scale);//to make it easier we update button constructor declaration to accpet parameters:Const char* imagepath, Vector2imagePosition
    ~Button();
    void Draw();
    bool isPressed(Vector2 mousePos,bool mousePressed);
  
};