/***********************************************************************************************
* 
*   text - The library for drawing formatted text.
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
/***********************************************************************************************
*
*   The main class for drawing stylized text to the screen.
*
*   ---------------------------------------- ARGUMENTS ----------------------------------------
*
*   int fontSize            Font size.
*
*   int letterSpacing       Pixels between letters.
*
*   Color textColor         Color of the main text.
*
*   Color shadowColor       Color of the shadow to display behind the main text.
*
*   const char * text       The string to display.
*
*   int textWidth           The width of the entire text block, after being formatted.
*
*   Vector2 origin          The center of both axes of the entire text block, after being
*                           formatted.
*
***********************************************************************************************/
{
    public:
        /* Text::Text --- Constructor. */
        Text(int fontSize, int letterSpacing, Color textColor, Color shadowColor, const char *text); 

        /* Text::Draw --- Draw the Text object centered on a position. */
        void Draw(Vector2 position);

    private:
        int fontSize;
        int letterSpacing;

        Color textColor;
        Color shadowColor;
        
        const char * text;
        int textWidth;
        Vector2 origin;
};
