/***********************************************************************************************
*
*   background.cpp - The library for creating and drawing backgrounds.
*
*   LICENSE: zlib/libpng 
*
*   Copyright (c) 2025 Josh Hayden (@BlinkDynamo)
*
*   This software is provided ‘as-is’, without any express or implied
*   warranty. In no event will the authors be held liable for any damages
*   arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose,
*   including commercial applications, and to alter it and redistribute it
*   freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not
*   claim that you wrote the original software. If you use this software
*   in a product, an acknowledgment in the product documentation would be
*   appreciated but is not required.
*
*   2. Altered source versions must be plainly marked as such, and must not be
*   misrepresented as being the original software.
*
*   3. This notice may not be removed or altered from any source
*   distribution. 
*
***********************************************************************************************/

// Source.
#include "background.hpp"

// Standard library.
#include <cmath>

Background::Background(
    int screenWidth,
    int screenHeight,
    Color darkColor,
    Color lightColor,
    float scrollOffset,
    int squareSize)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->darkColor = darkColor;
    this->lightColor = lightColor;
    this->scrollOffset = scrollOffset;
    this->squareSize = squareSize;
}

void Background::Update()
{
    scrollOffset += GetFrameTime() * 30.0f;
}

void Background::Draw()
{
    int cols = (screenWidth / squareSize) + 2;
    int rows = (screenHeight / squareSize) + 2;

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
