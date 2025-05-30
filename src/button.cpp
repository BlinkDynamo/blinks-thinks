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
    Label* label,
    Color bgColor,
    Vector2 pos,
    Vector2 size)
{
    this->label = label;
    this->bgColor = bgColor;
    this->size = size;
    this->position = pos;
    this->rect = {
        pos.x - (size.x / 2.0f),
        pos.y - (size.y / 2.0f),
        size.x,
        size.y
    };

    this->defaultLabelColor = label->getTextColor();
    this->currentLabelColor = defaultLabelColor;
    this->defaultBgColor = bgColor;
    this->currentBgColor = defaultBgColor;
    
    // Set the label's position to the button's position.
    this->label->setPosition(pos);
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
    // Update the color of the button's label if hovered.
    if (isHovered()) {
        float brightenFactor = 2.0f;
       
        // If the background is visible, brighten the background and darken the label.
        if (defaultBgColor.a != 0) {
            currentBgColor = { 
                static_cast<unsigned char>(fmin(defaultBgColor.r * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultBgColor.g * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultBgColor.b * brightenFactor, 255)),
                defaultBgColor.a
            };
            currentLabelColor = { 
                static_cast<unsigned char>(fmin(defaultLabelColor.r / brightenFactor, 0)),
                static_cast<unsigned char>(fmin(defaultLabelColor.g / brightenFactor, 0)),
                static_cast<unsigned char>(fmin(defaultLabelColor.b / brightenFactor, 0)),
                defaultLabelColor.a
            };
        }
        // Otherwise only brighten the label.
        else { 
            currentLabelColor = { 
                static_cast<unsigned char>(fmin(defaultLabelColor.r * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultLabelColor.g * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(defaultLabelColor.b * brightenFactor, 255)),
                defaultLabelColor.a
            };
        }
    } 
    else {
        currentBgColor = defaultBgColor;
        currentLabelColor = defaultLabelColor;
    }
    label->setTextColor(currentLabelColor);

    // Set the label's position to the button's position in case the button moves.
    label->setPosition(position);
}

void Button::Draw()
{
    // Draw the rectangle and label.
    DrawRectangleRec(rect, currentBgColor);
    label->Draw(); 
}

// ------------------------------------------------------------------------------------------ //
//                                     Factory functions.                                     //
// ------------------------------------------------------------------------------------------ //

// Make a clickable UI button with dynamic label and background color at a fixed location.
Button makeUiButton(const char* text)
{
    Vector2 position = { screenWidthCenter, screenHeightCenter + 100 };

    Label* label = new Label(text, 40, WHITE, { 0, 0, 0, 0 }, position);

    Button button(
        label,
        DARKGRAY,
        position,
        {180,60}
    );

    return button;
}

// Make clickable label by creating an invisible button in the shape and size of the label.
Button makeTextButton(const char* text, int fontSize, Color textColor, Vector2 position)
{
    Label* label = new Label(text, fontSize, textColor, { 15, 15, 15, 200 }, position);

    Button button(
        label,
        { 0, 0, 0, 0 },
        position,
        label->getTextDim()
    );
    
    return button;
}
