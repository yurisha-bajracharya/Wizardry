// #include "button1.hpp"

// //Button::Button() : texture{0}, position{0, 0} {}
// Button::Button(const char *imagepath, Vector2 imagePosition,float scale)
// {
//    Image image= LoadImage(imagepath);
//    int originalWidth=image.width;
//    int originalHeight=image.height;

//    int newwidth= static_cast<int>(originalWidth*scale);
//    int newHeight=static_cast<int>(originalHeight*scale);/*As scale is in float,and multiplying it with originalheight/width 
//                                                          makes the whole number floating point but using static_cast<int> provides more convinient
//                                                          way to type cast and convert it into integer number*/
//    ImageResize(&image, newwidth,newHeight);
//    texture=LoadTextureFromImage(image);
//    UnloadImage(image);
//     position= imagePosition;
// }
   
// /*Everytime we need to load a texture we need to unload it when the game is closed 
//  to free up the memory it requires. We will do that in the destructor because it is called
//  automatically when we close the game window*/

//  Button::~Button()
//  {
//     UnloadTexture(texture);
  
//  }

//  void Button::Draw()
//  {
//     DrawTextureV(texture,position,WHITE );/*This function draws a Texture2D with the 
//     position defines as Vector2, it's exactly what we need*/
//  }
//  bool Button::isPressed(Vector2 mousePos,bool mousePressed)
//  {
//    Rectangle rect={position.x,position.y, static_cast<float>(texture.width),static_cast<float>(texture.height)};

// if(CheckCollisionPointRec(mousePos, rect) && mousePressed)
// {
//    return true;

// }
// return false;
//  }