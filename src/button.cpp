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

#include "blinks-thinks/button.hpp"

Button::Button(Text& text, Color textHoverColor, Color bgDefaultColor, 
               Color bgHoverColor, Vector2 position, Vector2 size)
    : text(text), textHoverColor(textHoverColor), bgDefaultColor(bgDefaultColor), 
      bgHoverColor(bgHoverColor), position(position), size(size) 
{
    this->rect = { position.x - (size.x / 2.0f), position.y - (size.y / 2.0f), size.x, size.y };
    this->textDefaultColor = text.GetTextColor();
}

void Button::Draw()
{
    /* Set currentColor depending on if it's hovered or not. */
    Color currentBgColor;
    Color currentTextColor;
    
    if (CheckCollisionPointRec(GetMousePosition(), rect)) {
        currentBgColor = bgHoverColor;
        currentTextColor = textHoverColor;
    } 
    else {
        currentBgColor = bgDefaultColor;
        currentTextColor = textDefaultColor;
    }

    text.SetTextColor(currentTextColor);

    /* Draw the rectangle and text. */
    DrawRectangleRec(rect, currentBgColor);
    text.DrawStatic(position); 
}

bool Button::isPressed()
{
    return CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
}
