#pragma once

#include <raylib/raylib.h>

class Background 
{
    public:
        Background(int screenWidth, int screenHeight, Color darkColor, Color lightColor,
                   float scrollOffset, int squareSize);

        void Draw(float scrollOffset);

    private:
        int screenWidth;
        int screenHeight;
        Color darkColor;
        Color lightColor;
        float scrollOffset;
        int squareSize;
};
