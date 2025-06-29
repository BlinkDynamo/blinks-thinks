/***********************************************************************************************
*
*   button.hpp - The library for creating, drawing, and interacting with buttons.
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
#include "text.hpp"

namespace BlinkEngine
{
    class Button : public Entity {
        public:
            Button(
                Text* textObj,
                Color bgColor,
                Vector2 size,
                Vector2 position,
                int layer); 

            ~Button();

            void Update() override;
            void Draw() override;

            bool isHovered();           // Checks if the mouse is within the button's rectangle.

            bool isPressed();           // Checks if 'isHovered()' and the mouse being pressed
                                        // are both true.
            
            // Getters and setters.
            Text* getTextObj() { return m_textObj; }

            Rectangle getRectangle() { return m_rectangle; }

            void setScale(float scale) { m_scale = scale; }

        private:
            Text* m_textObj;            // The pointer to the text object of the button. The
                                        // button handles updating and drawing it's child text
                                        // within it's own 'Update()' and 'Draw()' methods.

            Vector2 m_size;             // The area the button's rectangle will occupy. Used to
                                        // calculate 'm_rectangle'.

            Rectangle m_rectangle;      // The rectangle used for most button actions. This is
                                        // calculated from 'm_size', 'm_position', and 'm_scale'.

            Color m_defaultTextColor;   // What color the text object's text should be when not
                                        // hovered.

            Color m_currentTextColor;   // What color the text object's text should be drawn in
                                        // the current frame.

            Color m_defaultBgColor;     // What color the button's background should be when not
                                        // hovered.

            Color m_currentBgColor;     // What color the button's background should be in the
                                        // current frame.

            float m_scale;              // What 'm_rectangle' and the text object's 'm_fontSize'
                                        // are multiplied by.
    };
}
