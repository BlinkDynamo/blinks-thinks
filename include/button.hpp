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

        // Class unique methods.
        bool isHovered();
        bool isPressed();

    private:
        // Arguments.
        Label* m_label;

        // Set during construction.
        Rectangle m_rect;

        Color m_defaultTextColor;
        Color m_currentTextColor;
        Color m_defaultBgColor;
        Color m_currentBgColor;
};

Button makeUiButton(const char* text);
Button makeTextButton(const char* text, int fontSize, Color textColor, Vector2 position);
