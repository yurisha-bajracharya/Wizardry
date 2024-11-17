#include "globals.h"

Font fontBold;
Font fontNormal;
Font semiItalic;
Font medium;

void InitFonts()
{
    fontBold = LoadFontEx("./font/Poppins-Bold.ttf", 200, 0, 0);
    fontNormal = LoadFontEx("./font/Poppins-Regular.ttf", 200, 0, 0);
    semiItalic = LoadFontEx("./font/Poppins-SemiBoldItalic.ttf", 200, 0, 0);
    medium = LoadFontEx("./font/Poppins-Medium.ttf", 200, 0, 0);
}

void UnloadFonts()
{
    UnloadFont(fontBold);
    UnloadFont(fontNormal);
    UnloadFont(semiItalic);
}