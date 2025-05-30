/***********************************************************************************************
*
*   background.cpp - The library for creating and drawing backgrounds.
*
*   Copyright (c) 2025 Josh Hayden (@BlinkDynamo)
*
*   Blink's Thinks is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License v3.0 as published
*   by the Free Software Foundation.
*  
*   Blink's Thinks is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*  
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
