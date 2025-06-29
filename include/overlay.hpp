/***********************************************************************************************
*
*   overlay.hpp - The library for creating and drawing overlays.
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

#pragma once

// Source.
#include "entity.hpp"

namespace BlinkEngine
{
    class Overlay : public Entity
    {
        public:
            Overlay(Color color);

            void setColor(Color color) { m_color = color; }

            void Update() override;
            void Draw() override;

        private:
            Color m_color;
    };
}
