/***********************************************************************************************
*
*   background.hpp - The library for creating and drawing backgrounds.
*
*   Copyright (c) 2025 Josh Hayden (@BlinkDynamo)
*
*   Blink's Thinks is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
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

class Background
{
    public:
        Background(
            int screenWidth,
            int screenHeight,
            Color darkColor,
            Color lightColor,
            float scrollOffset,
            int squareSize);

        void Update();
        void Draw();

    private:
        // Arguments.
        int screenWidth;
        int screenHeight;
        Color darkColor;
        Color lightColor;
        float scrollOffset;
        int squareSize;
};
