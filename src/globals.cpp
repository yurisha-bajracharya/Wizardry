#include "globals.h"

Font fontBold;
Font fontNormal;

void InitFonts()
{
    fontBold = LoadFontEx("./font/Poppins-Bold.ttf", 200, 0, 0);
    fontNormal = LoadFontEx("./font/Poppins-Regular.ttf", 200, 0, 0);
}

void UnloadFonts()
{
    UnloadFont(fontBold);
    UnloadFont(fontNormal);
}