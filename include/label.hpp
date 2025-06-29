/***********************************************************************************************
*
*   label.cpp - The library for creating, drawing, and interacting with a simple rectangle.
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
    class Label : public Entity {
        public:
            Label(
                Color lineColor,
                Color fillColor,
                Vector2 position,
                Vector2 size,
                int thickness,
                int layer); 

            void Update() override;
            void Draw() override;

            bool isHovered();           // Checks if 'mousePoint' (defined in 'include/main.hpp')
                                        // is within the bounds of 'm_rect'.

            bool isPressed();           // Checks if 'isHovered()', as well as 'mousePressed'
                                        // (also defined in 'include/main.hpp') are both true.

            // Getters and setters.
            void setScale(float scale) { m_scale = scale; }

            Rectangle getRectangle() { return m_rectangle; }

        private:
            Color m_lineColor;
            
            Color m_fillColor; 

            Vector2 m_size;             // The area the button's rectangle will occupy. Used to
                                        // calculate 'm_rectangle'.

            int m_thickness;            // The thickness of the shape's line.

            Rectangle m_rectangle;      // The rectangle used for most button actions. This is
                                        // calculated from 'm_size', 'm_position', and 'm_scale'. 

            float m_scale;              // What 'm_rectangle' and the label's 'm_fontSize' are
                                        // multiplied by.
    };
}
