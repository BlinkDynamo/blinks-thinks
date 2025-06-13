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

// Source.
#include "entity.hpp"

// Standard library.
#include <string>

using std::string;

class AnimRaylib : public Entity
{
    public:
        AnimRaylib();
        bool isFinished();
        void Update() override;
        void Draw() override;

    private:
        // Position.
        int m_logoPositionX;
        int m_logoPositionY;

        // Size.
        int m_topSideRecWidth;
        int m_leftSideRecHeight;
        int m_bottomSideRecWidth;
        int m_rightSideRecHeight;

        // Counters and state machines.
        int m_framesCounter;
        int m_lettersCount;
        int m_state;

        float m_alpha;
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
        int m_framesCounter;
        int m_lettersCount;
       
        // State of the animation.
        enum class State {
            LETTERS_ADDING,
            LETTERS_REMOVING,
            CURSOR_BLINKING,
            BLANK_SCREEN_DELAY,
            FINISHED
        };
        State m_state;

        // Text.
        string m_text;
        int m_fontSize;
        float m_spacing;
        Font m_font;
        Vector2 m_textPos;

        // Colors.
        Color m_bgColor;

        // Other.
        int m_shortDelay;

};
