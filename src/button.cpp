/***********************************************************************************************
*
*   button.cpp - The library for creating, drawing, and interacting with buttons.
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

#include "button.hpp"
#include "main.hpp"

#include <cmath>

/* ------------------------------------------------------------------------------------------ */
/*                                        Constructor.                                        */
/* ------------------------------------------------------------------------------------------ */
Button::Button(Text& text, Color bgColor, Vector2 position, Vector2 size)
    : text(text), bgColor(bgColor), position(position), size(size) 
{
    this->rect = { position.x - (size.x / 2.0f), position.y - (size.y / 2.0f), size.x, size.y };

    this->defaultTextColor = text.GetTextColor();
    this->currentTextColor = defaultTextColor;
    this->defaultBgColor = bgColor;
    this->currentBgColor = defaultBgColor;
}

/* ------------------------------------------------------------------------------------------ */
/*                                          Methods.                                          */
/* ------------------------------------------------------------------------------------------ */
bool Button::isHovered()
{
    return CheckCollisionPointRec(mousePoint, rect);
}

bool Button::isPressed()
{
    return isHovered() && mousePressed;
}

void Button::Update()
{     
    /* Update the color of the button's text if hovered. */
    if (isHovered()) {
        float brightenFactor = 1.2f;
        currentBgColor = { 
            (unsigned char) fmin(defaultBgColor.r * brightenFactor, 255),
            (unsigned char) fmin(defaultBgColor.g * brightenFactor, 255),
            (unsigned char) fmin(defaultBgColor.b * brightenFactor, 255),
            defaultBgColor.a
        };
        currentTextColor = { 
            (unsigned char) fmin(defaultTextColor.r * brightenFactor, 255),
            (unsigned char) fmin(defaultTextColor.g * brightenFactor, 255),
            (unsigned char) fmin(defaultTextColor.b * brightenFactor, 255),
            defaultTextColor.a
        };
    } 
    else {
        currentBgColor = defaultBgColor;
        currentTextColor = defaultTextColor;
    }

    text.SetTextColor(currentTextColor);
}

void Button::Draw()
{
    /* Draw the rectangle and text. */
    DrawRectangleRec(rect, currentBgColor);
    text.DrawStatic(position); 
}

/* ------------------------------------------------------------------------------------------ */
/*                                     Factory functions.                                     */
/* ------------------------------------------------------------------------------------------ */

/* Make a clickable UI button with dynamic text and background color at a fixed location. */
Button makeUiButton(const char * label)
{
    Text text(label, 40, WHITE, { 0, 0, 0, 0 });

    Button button(
        text,
        DARKGRAY,
        { screenWidthCenter, screenHeightCenter + 100 },
        {180,60}
    );

    return button;
}

/* Make clickable text by creating an invisible button in the shape and size of the text. */
Button makeTextButton(const char * label, int fontSize, Color textColor, Vector2 position)
{
    Text text(label, fontSize, textColor, { 15, 15, 15, 200 });

    Button button(
        text,
        { 0, 0, 0, 0 },
        position,
        text.GetTextDim()
    );

    return button;
}
