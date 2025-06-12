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
#include "label.hpp"

class Button : public Entity {
    public:
        Button(
            Label* label,
            Color bgColor,
            Vector2 position,
            Vector2 size); 

        ~Button();

        void Update() override;
        void Draw() override;

        bool isHovered();           // Checks if 'mousePoint' (defined in 'include/main.hpp') is
                                    // within the bounds of 'm_rect'.

        bool isPressed();           // Checks if 'isHovered()', as well as 'mousePressed' (also 
                                    // defined in 'include/main.hpp') are both true.

        // Getters and setters.
        Label* getLabel() { return m_label; }

        void setScale(float scale) { m_scale = scale; }

    private:
        Label* m_label;             // The pointer to the label of the button. The button
                                    // handles updating and drawing it's child label within
                                    // it's own 'Update()' and 'Draw()' methods.

        Vector2 m_size;             // The area the button's rectangle will occupy. Used to
                                    // calculate 'm_rect'.

        Rectangle m_rect;           // The rectangle used for most button actions. This is
                                    // calculated from 'm_size', 'm_position', and 'm_scale'.

        Color m_defaultTextColor;   // What color the label's text should be when not hovered.

        Color m_currentTextColor;   // What color the label's text should be drawn in the
                                    // current frame.

        Color m_defaultBgColor;     // What color the button's background should be when not
                                    // hovered.

        Color m_currentBgColor;     // What color the button's background should be in the
                                    // current frame.

        float m_scale;              // What 'm_rect' and the label's 'm_fontSize' are multiplied by.
};
