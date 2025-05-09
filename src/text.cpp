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

Text::Text(const char * text, int fontSize, Color textColor, Color shadowColor = { 0, 0, 0, 0 })
{
    /* All passed variables. */
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = textColor;
    this->shadowColor = shadowColor;

    /* Variables calculated on construction. */
    this->letterSpacing = fontSize / 10.0f;
    this->textWidth = MeasureText(text, fontSize);
    this->origin = { textWidth / 2.0f, fontSize / 2.0f };
}

void Text::DrawStatic(Vector2 position)
{
    Vector2 shadowOffset = { 6.0f, 6.0f };

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

void Text::DrawWobbling(Vector2 position, float animationSpeed, float animationDepth)
{
    /* Rotation. */
    static float rotation = 0.0f;
    rotation = sin(GetTime() * animationSpeed) * animationDepth;

    Vector2 shadowOffset = { 6.0f, 6.0f };

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
