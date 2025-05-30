/***********************************************************************************************
*
*   text.cpp - The library for creating and drawing formatted text.
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

// Raylib.
#include "raylib.h"

// Source.
#include "text.hpp"

// Standard library.
#include <cmath>

Text::Text(
    const char* text,
    int fontSize,
    Color textColor,
    Color shadowColor,
    Vector2 position)
{
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->shadowColor = shadowColor;
    this->position = position;

    this->letterSpacing = fontSize / 10.0f;
    this->textDim = MeasureTextEx(GetFontDefault(), text, fontSize, letterSpacing);
    this->origin = { textDim.x / 2.0f, textDim.y / 2.0f };
    this->shadowOffset = { 5.0f, 5.0f };
}

void Text::Update()
{

}

void Text::Draw()
{
    // Shadow. Only draw the shadow if it's not fully transparent.
    if (shadowColor.a != 0) {
        DrawTextPro(
            GetFontDefault(), 
            text, 
            { position.x + shadowOffset.x, position.y + shadowOffset.y }, 
            origin,
            0,
            fontSize,
            letterSpacing,
            shadowColor);
    }

    // Text.
    DrawTextPro(
        GetFontDefault(),
        text,
        position,
        origin,
        0,
        fontSize,
        letterSpacing,
        textColor);
}

void Text::drawWobbling(float animationSpeed, float animationDepth)
{
    // Rotation.
    static float rotation = 0.0f;
    rotation = sin(GetTime() * animationSpeed) * animationDepth;

    // Shadow. Only draw the shadow if it's not fully transparent.
    if (shadowColor.a != 0) {
        DrawTextPro(
            GetFontDefault(), 
            text, 
            { position.x + shadowOffset.x, position.y + shadowOffset.y }, 
            origin,
            rotation,
            fontSize,
            letterSpacing,
            shadowColor);
    }

    // Text.
    DrawTextPro(
        GetFontDefault(),
        text,
        position,
        origin,
        rotation,
        fontSize,
        letterSpacing,
        textColor);
}
