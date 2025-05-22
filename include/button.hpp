/***********************************************************************************************
*
*   button.hpp - The library for creating, drawing, and interacting with buttons.
*
*   LICENSE: zlib/libpng 
*
*   Copyright (c) 2025 Josh Hayden (@BlinkDynamo)
*
*   This software is provided ‘as-is’, without any express or implied
*   warranty. In no event will the authors be held liable for any damages
*   arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose,
*   including commercial applications, and to alter it and redistribute it
*   freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not
*   claim that you wrote the original software. If you use this software
*   in a product, an acknowledgment in the product documentation would be
*   appreciated but is not required.
*
*   2. Altered source versions must be plainly marked as such, and must not be
*   misrepresented as being the original software.
*
*   3. This notice may not be removed or altered from any source
*   distribution. 
*
***********************************************************************************************/

#pragma once

// Raylib.
#include "raylib.h"

#include "entity.hpp"
#include "text.hpp"

#include <string>

class Button : public Entity {
    public:
        Button(
            Text* text,
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
        Text* text;
        Color bgColor;
        Vector2 position;
        Vector2 size; 

        // Set during construction.
        Color defaultTextColor;
        Color currentTextColor;
        Color defaultBgColor;
        Color currentBgColor;

        Rectangle rect;
};

Button makeUiButton(const char* label);
Button makeTextButton(const char* label, int fontSize, Color textColor, Vector2 position);
