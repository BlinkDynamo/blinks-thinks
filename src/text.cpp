/***********************************************************************************************
*
*   text.cpp - The library for creating and drawing formatted text.
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
#include "text.hpp"

using engine::text;

// Standard library.
#include <cmath>

text::text(
    string text_str,
    float font_size,
    Color text_color,
    Color shadow_color,
    Vector2 position,
    int layer)

    :
    entity(position, layer),

    m_text_str(text_str),
    m_scale(1.0f),

    m_base_font_size(font_size),
    m_scaled_font_size(m_base_font_size * m_scale),

    m_text_color(text_color),
    m_shadow_color(shadow_color),
    
    // Updated every frame in update().
    m_letter_spacing(m_base_font_size / 10.0f),
    m_text_dim(MeasureTextEx(GetFontDefault(), m_text_str.c_str(), m_base_font_size, m_letter_spacing)),
    m_origin({ m_text_dim.x / 2.0f, m_text_dim.y / 2.0f }),

    // Constants.
    m_shadow_offset({ 5.0f, 5.0f }),
    
    // Set to 0, with the prospect of being set at a later time.
    m_rotation(0.0f),
    m_rotation_speed(0.0f),
    m_rotation_depth(0.0f)
{}

void text::update()
{ 
    entity::update();

    // update the scaled font size in case scale has changed since last frame. 
    m_scaled_font_size = m_base_font_size * m_scale;
    
    m_letter_spacing = m_scaled_font_size / 10.0f;
    m_text_dim = MeasureTextEx(GetFontDefault(), m_text_str.c_str(), m_scaled_font_size, m_letter_spacing);
    m_origin = { m_text_dim.x / 2.0f, m_text_dim.y / 2.0f };
    m_rotation = sin(GetTime() * m_rotation_speed) * m_rotation_depth;
}

void text::draw()
{
    // Shadow. Only draw the shadow if it's not fully transparent.
    if (m_shadow_color.a != 0) {
        DrawTextPro(
            GetFontDefault(), 
            m_text_str.c_str(), 
            { m_position.x + m_shadow_offset.x, m_position.y + m_shadow_offset.y }, 
            m_origin,
            m_rotation,
            m_scaled_font_size,
            m_letter_spacing,
            m_shadow_color);
    }

    // text.
    DrawTextPro(
        GetFontDefault(),
        m_text_str.c_str(),
        m_position,
        m_origin,
        m_rotation,
        m_scaled_font_size,
        m_letter_spacing,
        m_text_color);
}
