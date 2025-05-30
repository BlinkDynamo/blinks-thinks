/***********************************************************************************************
*
*   button.cpp - The library for creating, drawing, and interacting with buttons.
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
#include "button.hpp"
#include "main.hpp"

// Standard library.
#include <cmath>

Button::Button(
    Text* text,
    Color bgColor,
    Vector2 pos,
    Vector2 size)
{
    this->text = text;
    this->bgColor = bgColor;
    this->size = size;
    this->position = pos;
    this->rect = {
        pos.x - (size.x / 2.0f),
        pos.y - (size.y / 2.0f),
        size.x,
        size.y
    };

    this->defaultTextColor = text->getTextColor();
    this->currentTextColor = defaultTextColor;
    this->defaultBgColor = bgColor;
    this->currentBgColor = defaultBgColor;
    
    // Set the text's position to the button's position.
    this->text->setPosition(pos);
}

// ------------------------------------------------------------------------------------------ //
//                                          Methods.                                          //
// ------------------------------------------------------------------------------------------ //
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
    // Update the color of the button's text if hovered.
    if (isHovered()) {
        float brightenFactor = 2.0f;
       
        // If the background is visible, brighten the background and darken the text.
        if (defaultBgColor.a != 0) {
            currentBgColor = { 
                static_cast<unsigned char>(fmin(defaultBgColor.r * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultBgColor.g * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultBgColor.b * brightenFactor, 255)),
                defaultBgColor.a
            };
            currentTextColor = { 
                static_cast<unsigned char>(fmin(defaultTextColor.r / brightenFactor, 0)),
                static_cast<unsigned char>(fmin(defaultTextColor.g / brightenFactor, 0)),
                static_cast<unsigned char>(fmin(defaultTextColor.b / brightenFactor, 0)),
                defaultTextColor.a
            };
        }
        // Otherwise only brighten the text.
        else { 
            currentTextColor = { 
                static_cast<unsigned char>(fmin(defaultTextColor.r * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultTextColor.g * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultTextColor.b * brightenFactor, 255)),
                defaultTextColor.a
            };
        }
    } 
    else {
        currentBgColor = defaultBgColor;
        currentTextColor = defaultTextColor;
    }
    text->setTextColor(currentTextColor);

    // Set the text's position to the button's position in case the button moves.
    text->setPosition(position);
}

void Button::Draw()
{
    // Draw the rectangle and text.
    DrawRectangleRec(rect, currentBgColor);
    text->Draw(); 
}

// ------------------------------------------------------------------------------------------ //
//                                     Factory functions.                                     //
// ------------------------------------------------------------------------------------------ //

// Make a clickable UI button with dynamic text and background color at a fixed location.
Button makeUiButton(const char* label)
{
    Vector2 position = { screenWidthCenter, screenHeightCenter + 100 };

    Text* text = new Text(label, 40, WHITE, { 0, 0, 0, 0 }, position);

    Button button(
        text,
        DARKGRAY,
        position,
        {180,60}
    );

    return button;
}

// Make clickable text by creating an invisible button in the shape and size of the text.
Button makeTextButton(const char* label, int fontSize, Color textColor, Vector2 position)
{
    Text* text = new Text(label, fontSize, textColor, { 15, 15, 15, 200 }, position);

    Button button(
        text,
        { 0, 0, 0, 0 },
        position,
        text->getTextDim()
    );
    
    return button;
}
