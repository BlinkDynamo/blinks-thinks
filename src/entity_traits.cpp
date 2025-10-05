/***********************************************************************************************
*
*   entity_traits.cpp - The library for adding traits to existing entities.
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
#include "entity_traits.hpp"
#include "game.hpp"

using engine::game;
using engine::button_trait;
using engine::grows_when_hovered;

grows_when_hovered::grows_when_hovered(int frame_duration, float target_scale)
{
    this->m_frame_duration = frame_duration;
    this->m_target_scale = target_scale;
    this->m_default_scale = 1.0f;
}

void grows_when_hovered::update(button& btn)
{
    m_current_scale = btn.get_scale();

    if (btn.is_hovered()) {
        if (!game::float_equals(m_current_scale, m_target_scale)) {
            // Compute per-frame delta.
            float delta = (m_target_scale - m_current_scale) / m_frame_duration;
            m_current_scale += delta;

            // Snap if overshoot.
            if ((delta > 0 && m_current_scale > m_target_scale) ||
                (delta < 0 && m_current_scale < m_target_scale)) {
                m_current_scale = m_target_scale;
            }
        }
    }
    else if (!game::float_equals(m_current_scale, m_default_scale)) {
        float delta = (m_default_scale - m_current_scale) / m_frame_duration;
        m_current_scale += delta;

        if ((delta > 0 && m_current_scale > m_default_scale) ||
            (delta < 0 && m_current_scale < m_default_scale)) {
            m_current_scale = m_default_scale;
        }
    }

    btn.set_scale(m_current_scale);
}
