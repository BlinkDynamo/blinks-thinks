/***********************************************************************************************
* 
*   label.hpp - The library for creating and drawing formatted text.
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

// Source.
#include "entity.hpp"

class Label : public Entity
{
    public:
        Label(
            const char* text,
            int fontSize,
            Color textColor,
            Color shadowColor,
            Vector2 position); 

        void drawWobbling(float animationSpeed, float animationDepth);

        virtual void Update();
        virtual void Draw();

        virtual Vector2 getPosition() { return position; }
        virtual void setPosition(Vector2 pos) { position = pos; }

        Color getTextColor() { return textColor; }
        void setTextColor(Color tc) { textColor = tc; }

        Vector2 getTextDim() { return textDim; }
        void setTextDim(Vector2 td) { textDim = td; }

    private:
        // Arguments.
        const char* text;
        int fontSize;
        Color textColor;
        Color shadowColor;
        Vector2 position;
       
        // Set during construction.
        int letterSpacing;
        Vector2 textDim;
        Vector2 origin;
        Vector2 shadowOffset;
};
