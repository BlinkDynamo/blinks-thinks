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

// Raylib.
#include "raylib.h"

#include "entity.hpp"
#include "label.hpp"

class Button : public Entity {
    public:
        Button(
            Label* label,
            Color bgColor,
            Vector2 pos,
            Vector2 size); 
        
        virtual void Update();
        virtual void Draw(); 

        // Class unique methods.
        bool isHovered();
        bool isPressed();

    private:
        // Arguments.
        Label* label;
        Vector2 position;

        // Set during construction.
        Rectangle rect;

        Color defaultTextColor;
        Color currentTextColor;
        Color defaultBgColor;
        Color currentBgColor;
};

Button makeUiButton(const char* text);
Button makeTextButton(const char* text, int fontSize, Color textColor, Vector2 position);
