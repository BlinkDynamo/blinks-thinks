/***********************************************************************************************
*
*   label.cpp - The library for creating and drawing formatted text.
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
#include "label.hpp"

// Standard library.
#include <cmath>

Label::Label(
    const char* text,
    int fontSize,
    Color textColor,
    Color shadowColor,
    Vector2 position)
    
    :
    // Arguments.
    Entity(position),
    m_text(text),
    m_fontSize(fontSize),
    m_textColor(textColor),
    m_shadowColor(shadowColor),
    // Set here.
    m_letterSpacing(fontSize / 10.0f),
    m_textDim(MeasureTextEx(GetFontDefault(), m_text, m_fontSize, m_letterSpacing)),
    m_origin({ m_textDim.x / 2.0f, m_textDim.y / 2.0f }),
    m_shadowOffset({ 5.0f, 5.0f }),
    // Set to 0, with the prospect of being set at a later time.
    m_rotation(0.0f),
    m_rotationSpeed(0.0f),
    m_rotationDepth(0.0f)
{}

void Label::Update()
{
    m_rotation = sin(GetTime() * m_rotationSpeed) * m_rotationDepth;
}

void Label::Draw()
{
    // Shadow. Only draw the shadow if it's not fully transparent.
    if (m_shadowColor.a != 0) {
        DrawTextPro(
            GetFontDefault(), 
            m_text, 
            { m_position.x + m_shadowOffset.x, m_position.y + m_shadowOffset.y }, 
            m_origin,
            m_rotation,
            m_fontSize,
            m_letterSpacing,
            m_shadowColor);
    }

    // Label.
    DrawTextPro(
        GetFontDefault(),
        m_text,
        m_position,
        m_origin,
        m_rotation,
        m_fontSize,
        m_letterSpacing,
        m_textColor);
}
