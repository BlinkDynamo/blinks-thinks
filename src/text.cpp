/***********************************************************************************************
*
*   text.cpp - The library for creating and drawing formatted text.
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

#include "raylib/raylib.h"

#include "text.hpp"

#include <cmath>

Text::Text(const char* text, int fontSize, Color textColor, Color shadowColor, Vector2 position)
{
    /* All passed variables. */
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->shadowColor = shadowColor;
    this->position = position;

    /* Variables calculated on construction. */
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
    /* Shadow. Only draw the shadow if it's not fully transparent. */
    if (shadowColor.a != 0) {
        DrawTextPro(
            GetFontDefault(), 
            text, 
            (Vector2){ position.x + shadowOffset.x, position.y + shadowOffset.y }, 
            origin,
            0,
            fontSize,
            letterSpacing,
            shadowColor
        );
    }

    /* Text. */ 
    DrawTextPro(
        GetFontDefault(),
        text,
        position,
        origin,
        0,
        fontSize,
        letterSpacing,
        textColor
        );
}

void Text::drawWobbling(Vector2 position, float animationSpeed, float animationDepth)
{
    /* Rotation. */
    static float rotation = 0.0f;
    rotation = sin(GetTime() * animationSpeed) * animationDepth;

    /* Shadow. Only draw the shadow if it's not fully transparent. */
    if (shadowColor.a != 0) {
        DrawTextPro(
            GetFontDefault(), 
            text, 
            (Vector2){ position.x + shadowOffset.x, position.y + shadowOffset.y }, 
            origin,
            rotation,
            fontSize,
            letterSpacing,
            shadowColor
        );
    }

    /* Text. */ 
    DrawTextPro(
        GetFontDefault(),
        text,
        position,
        origin,
        rotation,
        fontSize,
        letterSpacing,
        textColor
        );
}
