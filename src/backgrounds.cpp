#include "raylib/raylib.h"

#include <cmath>

void DrawScrollingCheckerboard (
        int screenWidth, 
        int screenHeight, 
        Color darkColor,
        Color lightColor,
        float scrollOffset, 
        int squareSize
        )
{
    int cols = screenWidth / squareSize + 2;
    int rows = screenHeight / squareSize + 2;

    float effectiveOffset = std::fmod(scrollOffset, 2 * squareSize);

    for (int y = -2; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            bool isDark = (x + y) % 2 == 0;
            Color color = isDark ? darkColor : lightColor;

            float drawX = x * squareSize;
            float drawY = y * squareSize + effectiveOffset;

            DrawRectangle(drawX, drawY, squareSize, squareSize, color);
        }
    }
}
