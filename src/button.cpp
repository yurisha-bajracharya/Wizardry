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
void Button::Draw(Texture2D texture, Vector2 position, float scale)
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
bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    if (CheckCollisionPointRec(mousePos, rect) && mousePressed)
    {
        return true;
    }
    else
    {
        return false;
    }
}