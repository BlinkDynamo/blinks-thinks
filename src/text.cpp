/***********************************************************************************************
*
*   text - The library for drawing formatted text.
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

#include "blinks-thinks/text.hpp"

#include <cmath>

Text::Text(int fontSize, int letterSpacing, Color textColor, Color shadowColor, 
           const char * text)
{
    /* All passed variables. */
    this->fontSize = fontSize;
    this->letterSpacing = letterSpacing;
    this->textColor = textColor;
    this->shadowColor = shadowColor;
    this->text = text;

    /* Variables calculated on construction. */
    this->textWidth = MeasureText(text, fontSize);
    this->origin = { textWidth / 2.0f, fontSize / 2.0f };
}

void Text::Draw(Vector2 position)
{
    /* Rotation */
    static float rotation = 0.0f;
    rotation = sin(GetTime()) * 7.0f;

    Vector2 shadowOffset = { 6.0f, 6.0f };

    /* Shadow. */
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
