/***********************************************************************************************
* 
*   text.hpp - The library for creating and drawing formatted text.
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

#include <raylib/raylib.h>

#include <string>

class Text
{
    public:
        Text(const char *text, int fontSize, Color textColor, Color shadowColor); 

        void DrawStatic(Vector2 position);
        void DrawWobbling(Vector2 position, float animationSpeed, float animationDepth);

        Color GetTextColor() { return textColor; }
        void SetTextColor(Color tc) { textColor = tc; }

        Vector2 GetTextDim() { return textDim; }
        void SetTextDim(Vector2 td) { textDim = td; }

    private:
        /* Arguments. */
        const char * text;
        int fontSize;
        Color textColor;
        Color shadowColor;
       
        /* Set during construction. */ 
        int letterSpacing;
        Vector2 textDim;
        Vector2 origin;
        Vector2 shadowOffset;
};
