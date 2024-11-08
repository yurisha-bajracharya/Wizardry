#include "button.hpp"



Button::Button(const char* imagepath, Vector2 imageposition,float scale)
{
    Image image=LoadImage(imagepath);
    int originalwidth=image.width;
    int originalheight=image.height;
    int newwidth=static_cast<int>(originalwidth*scale);
    int newheight=static_cast<int>(originalheight*scale);
    ImageResize(&image,newwidth,newheight);
    texture=LoadTextureFromImage(image);
    UnloadImage(image);
    position =imageposition;
}
Button::~Button()
{
    UnloadTexture(texture);
}
void Button::Draw()
{
    DrawTextureV(texture,position,WHITE);
}
 bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect={position.x,position.y,static_cast<float>(texture.width),static_cast<float>(texture.height)};
     if(CheckCollisionPointRec(mousePos,rect)&& mousePressed)
    {
        return true;
     } 
      else
     {
    return false;     
    }
 }