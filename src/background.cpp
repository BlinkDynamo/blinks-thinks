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

    : 
    Entity({0, 0}), // Set this to 0, 0 for now. Position is unused.
    m_screenWidth(screenWidth),
    m_screenHeight(screenHeight),
    m_darkColor(darkColor),
    m_lightColor(lightColor),
    m_scrollOffset(scrollOffset),
    m_squareSize(squareSize)
{}

void Background::Update()
{
    m_scrollOffset += GetFrameTime() * 30.0f;
}

void Background::Draw()
{
    int cols = (m_screenWidth / m_squareSize) + 2;
    int rows = (m_screenHeight / m_squareSize) + 2;

    float effectiveOffset = std::fmod(m_scrollOffset, 2 * m_squareSize);

    for (int y = -2; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            bool isDark = (x + y) % 2 == 0;
            Color color = isDark ? m_darkColor : m_lightColor;

            float drawX = x * m_squareSize;
            float drawY = y * m_squareSize + effectiveOffset;

            DrawRectangle(drawX, drawY, m_squareSize, m_squareSize, color);
        }
    }
}
