/**********************************************************************************************
*
*   button - The class library for buttons within the game.
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
*********************************************************************************************/

#include "blinks-thinks/button.hpp"

Button::Button(const char * text, int fontSize, Vector2 position, Vector2 size, Color bgColor,
               Color textColor)
{
    this->text = text;
    this->fontSize = fontSize;
    /* 'position' places the button based on it's center position. */
    this->position = {position.x -= size.x / 2.0f, position.y -= size.y / 2.0f };
    this->size = size;
    this->bgColor = bgColor;
    this->textColor = textColor;
}

void Button::Draw()
{
    DrawRectangleV(position, size, bgColor);

    /* Center the text inside the button. */
    int textWidth = MeasureText(text, fontSize);
    int textX = position.x + (size.x - textWidth) / 2;
    int textY = position.y + (size.y - fontSize) / 2;

    DrawText(text, textX, textY, fontSize, textColor);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect = { position.x, position.y, size.x, size.y };
    return CheckCollisionPointRec(mousePos, rect) && mousePressed;
}
