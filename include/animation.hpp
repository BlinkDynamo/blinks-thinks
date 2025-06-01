/***********************************************************************************************
*
*   animation.hpp - The library for drawing animations.
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

class AnimRaylib : public Entity
{
    public:
        AnimRaylib();
        bool isFinished();
        void Update() override;
        void Draw() override;

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

class AnimSelfCredit : public Entity
{
    public:
        AnimSelfCredit();
        bool isFinished();
        void Draw() override;
        void Update() override;

    private:
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
       
        // Text.
        const char* text;
        int fontSize;
        float spacing;
        Font font;
        Vector2 textPos;

        // Colors.
        Color bgColor;

        // Other.
        int shortDelay;

};
