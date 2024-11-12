#pragma once
#include "C:\raylib\raylib\src\raylib.h"

class Button
{
public:
Button();
  Button(const char *imagepath, Vector2 imageposition, float scale);
  ~Button();
  void Draw();
  bool isPressed(Vector2 mousePos, bool mousePressed);

private:
  Texture texture;
  Vector2 position;
};