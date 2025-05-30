/***********************************************************************************************
*
*   splash_screen.hpp - The library for drawing splash screens.
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
       
        // Colors and alpha.
        Color bgColor;
        float alpha;

        // Other.
        int shortDelay;

};
