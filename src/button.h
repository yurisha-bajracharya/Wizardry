#pragma once
#include "C:\raylib\raylib\src\raylib.h"

class Button
{
public:
  Button(); 
  ~Button();
  void Draw(Texture2D texture, float scale);
  bool isPressed(Vector2 mousePos, bool mousePressed, Vector2 position, float scale);
  void SetPosition(float x, float y);
  Texture2D texture;
  Vector2 position;
  float scale;
};