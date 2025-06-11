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
    Vector2 position,
    Vector2 size)

    :
    // Arguments.
    Entity(position),
    m_label(label),
    m_position(position),
    m_size(size),

    // Updated every frame in 'Update()'.
    m_rect({m_position.x - (m_size.x / 2.0f), m_position.y - (m_size.y / 2.0f), m_size.x, m_size.y}),

    // Set once here, but are still mutable.
    m_defaultTextColor(label->getTextColor()),
    m_currentTextColor(m_defaultTextColor),
    m_defaultBgColor(bgColor),
    m_currentBgColor(m_defaultBgColor),
    m_scale(1.0f)
{
    this->m_label->setPosition(position);
}

Button::~Button() {
    delete m_label;
}

// ------------------------------------------------------------------------------------------ //
//                                          Methods.                                          //
// ------------------------------------------------------------------------------------------ //
bool Button::isHovered()
{
    return CheckCollisionPointRec(mousePoint, m_rect);
}

bool Button::isPressed()
{
    return isHovered() && mousePressed;
}

void Button::Update()
{ 
    // Update the rectangle, multiplying size elements by scale.
    m_rect = {
        m_position.x - ((m_size.x * m_scale) / 2.0f),
        m_position.y - ((m_size.y * m_scale) / 2.0f),
        m_size.x * m_scale,
        m_size.y * m_scale
    };

    // Update the label's scale so that it's Update() step can multiply the font size by scale.
    m_label->setScale(m_scale);

    // Set the label's position to the button's position in case the button moves.
    m_label->setPosition(m_position);

    // Update the color of the button's label if hovered.
    if (isHovered()) {
        float brightenFactor = 2.0f;

        // If the background is visible, brighten the background and darken the label.
        if (m_defaultBgColor.a != 0) {
            m_currentBgColor = { 
                static_cast<unsigned char>(fmin(m_defaultBgColor.r * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(m_defaultBgColor.g * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(m_defaultBgColor.b * brightenFactor, 255)),
                m_defaultBgColor.a
            };
            m_currentTextColor = { 
                static_cast<unsigned char>(fmin(m_defaultTextColor.r / brightenFactor, 0)),
                static_cast<unsigned char>(fmin(m_defaultTextColor.g / brightenFactor, 0)),
                static_cast<unsigned char>(fmin(m_defaultTextColor.b / brightenFactor, 0)),
                m_defaultTextColor.a
            };
        }
        // Otherwise only brighten the label.
        else { 
            m_currentTextColor = { 
                static_cast<unsigned char>(fmin(m_defaultTextColor.r * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(m_defaultTextColor.g * brightenFactor, 255)),
                static_cast<unsigned char>(fmin(m_defaultTextColor.b * brightenFactor, 255)),
                m_defaultTextColor.a
            };
        }
    }
    else {
        m_currentBgColor = m_defaultBgColor;
        m_currentTextColor = m_defaultTextColor;
    }
    m_label->setTextColor(m_currentTextColor); 

    // Update the label.
    m_label->Update();
}

void Button::Draw()
{
    // Draw the rectangle and label.
    DrawRectangleRec(m_rect, m_currentBgColor);
    m_label->Draw(); 
}
