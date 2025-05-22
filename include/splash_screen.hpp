/***********************************************************************************************
*
*   splash_screen.hpp - The library for drawing splash screens.
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

class RaylibSplash
{
    public:
        RaylibSplash();
        bool isFinished();
        void Update();
        void Draw();

    private:
        // Position.
        int logoPositionX;
        int logoPositionY;

        // Size.
        int topSideRecWidth;
        int leftSideRecHeight;
        int bottomSideRecWidth;
        int rightSideRecHeight;

        // Counters and state machines.
        int framesCounter;
        int lettersCount;
        int state;

        float alpha;
};

class BlinkSoftwareSplash
{
    public:
        BlinkSoftwareSplash();
        bool isFinished();
        void Draw();
        void Update();

    private:
        // Position.
        int logoPositionX;
        int logoPositionY;

        // Counters.
        int framesCounter;
        int lettersCount;
       
        // State of the animation. 
        enum class State {
            LETTERS_ADDING,
            LETTERS_REMOVING,
            CURSOR_BLINKING,
            BLANK_SCREEN_DELAY,
            FINISHED
        };
        State state;
       
        // Other. 
        float alpha;

        int shortDelay;

};
