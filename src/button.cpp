#include "button.h"
#include <iostream>
#include "C:\raylib\raylib\src\raylib.h"

using namespace std;

Button::Button() : texture{0}, position{0, 0}, scale{1.0f}
{
}

Button::~Button()
{
    if (texture.id != 0)
    {
        UnloadTexture(texture);
    }
}
void Button::Draw(Texture2D texture, float scale)
{
    if (texture.id != 0)
    {
        DrawTextureEx(texture, position, 0.0f, scale, WHITE); // syntax: DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
    }
    else
    {
        cout << "Texture not loaded, button texturee" << endl;
    }
}
bool Button::isPressed(Vector2 mousePos, bool mousePressed, Vector2 position, float scale, float width, float height)
{
    Rectangle rect = {position.x, position.y, width, height};//syntax: Rectangle(float x, float y, float width, float height)
    cout << "mousepressed: " << mousePressed << endl;
    if (CheckCollisionPointRec(mousePos, rect) && mousePressed)
    {
        return true;
        cout << "Button is pressed!!!" << endl;
        cout << "Mouse position: " << mousePos.x << ", " << mousePos.y << endl;
        cout << "Button position: " << position.x << ", " << position.y << endl;
    }
    else
    {
        return false;
    }
}

void Button::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}