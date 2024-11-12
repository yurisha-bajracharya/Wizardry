#pragma once
#include "C:\raylib\raylib\src\raylib.h"

class Button
{
public:
Button();
  // Button(const char *imagepath, Vector2 imageposition, float scale);
  ~Button();
  void Draw(Texture2D texture, Vector2 position, float scale);
  bool isPressed(Vector2 mousePos, bool mousePressed);

private:
  Texture2D texture;
  Vector2 position;
  float scale;
};