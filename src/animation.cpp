/***********************************************************************************************
*
*   animation.cpp - The library for drawing animations.
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

// Source.
#include "animation.hpp"
#include "main.hpp"

using BlinkEngine::AnimRaylib;
using BlinkEngine::AnimSelfCredit;

// ------------------------------------------------------------------------------------------ //
//                                   Raylib splash screen.                                    //
// ------------------------------------------------------------------------------------------ //
AnimRaylib::AnimRaylib()
    :
    Entity({0, 0}, 0), // Both of these are unused. Set default values of 0.
    m_logoPositionX((G_w / 2) - 128),
    m_logoPositionY((G_h / 2) - 128),
    m_topSideRecWidth(16),
    m_leftSideRecHeight(16),
    m_bottomSideRecWidth(16),
    m_rightSideRecHeight(16),
    m_framesCounter(0),
    m_lettersCount(0),
    m_state(0),
    m_alpha(1.0f)
{}

bool AnimRaylib::isFinished()
{
    return (m_state == 4);
}

void AnimRaylib::Update()
/***********************************************************************************************
*
*   Original animation courtesy of Ramon Santamaria (@raysan5)
*
*   This code has been changed from the original source code found here:
*       
*   https://github.com/raysan5/raylib/examples/shapes/shapes_logo_raylib_anim.c
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
***********************************************************************************************/
{
    switch (m_state)
    {
        case (0): {
            m_framesCounter++;

            if (m_framesCounter == 120)
            {
                m_state = 1;
                m_framesCounter = 0;      // Reset counter... will be used later...
            }
        } break;

        case (1): {
            m_topSideRecWidth += 4;
            m_leftSideRecHeight += 4;

            if (m_topSideRecWidth == 256) m_state = 2;
        } break;

        case (2): {
        m_bottomSideRecWidth += 4;
        m_rightSideRecHeight += 4;

        if (m_bottomSideRecWidth == 256) m_state = 3;
        } break;

        case (3): { 
            m_framesCounter++;

            if (m_framesCounter/12)
            {
                m_lettersCount++;
                m_framesCounter = 0;
            }

            if (m_lettersCount >= 10)
            {
                m_alpha -= 0.02f;

                if (m_alpha <= 0.0f)
                {
                    m_alpha = 0.0f;
                    m_state = 4;
                }
            }
        } break;

        case (4): {} break;
    }
}

void AnimRaylib::Draw()
/***********************************************************************************************
*
*   Original animation courtesy of Ramon Santamaria (@raysan5)
*
*   This code has been changed from the original source code found here:
*       
*   https://github.com/raysan5/raylib/examples/shapes/shapes_logo_raylib_anim.c
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
***********************************************************************************************/
{
    ClearBackground(RAYWHITE);
    
    switch (m_state)
    {
        case (0): {
            if ((m_framesCounter / 15) % 2) {
                DrawRectangle(m_logoPositionX, m_logoPositionY, 16, 16, BLACK);
            }
        } break;

        case (1): {
            DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, BLACK);
            DrawRectangle(m_logoPositionX, m_logoPositionY, 16, m_leftSideRecHeight, BLACK);
        } break;

        case (2): {
            DrawRectangle(m_logoPositionX, m_logoPositionY, m_topSideRecWidth, 16, BLACK);
            DrawRectangle(m_logoPositionX, m_logoPositionY, 16, m_leftSideRecHeight, BLACK);

            DrawRectangle(m_logoPositionX + 240, m_logoPositionY, 16, m_rightSideRecHeight, BLACK);
            DrawRectangle(m_logoPositionX, m_logoPositionY + 240, m_bottomSideRecWidth, 16, BLACK);
        } break;

        case (3): {
            DrawRectangle(
                m_logoPositionX,
                m_logoPositionY,
                m_topSideRecWidth,
                16,
                Fade(BLACK, m_alpha));

            DrawRectangle(
                m_logoPositionX,
                m_logoPositionY + 16,
                16,
                m_leftSideRecHeight - 32,
                Fade(BLACK, m_alpha));

            DrawRectangle(
                m_logoPositionX + 240,
                m_logoPositionY + 16,
                16,
                m_rightSideRecHeight - 32,
                Fade(BLACK, m_alpha));

            DrawRectangle(
                m_logoPositionX,
                m_logoPositionY + 240,
                m_bottomSideRecWidth, 16,
                Fade(BLACK, m_alpha));

            DrawRectangle(
                GetScreenWidth()/2 - 112,
                GetScreenHeight()/2 - 112,
                224,
                224,
                Fade(RAYWHITE, m_alpha));

            DrawText(
                TextSubtext("raylib", 0, m_lettersCount),
                G_w/2 - 44,
                G_h/2 + 48,
                50,
                Fade(BLACK, m_alpha));

        } break;

        case (4): {
            return;
        } break;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                 Self credit splash screen.                                 //
// ------------------------------------------------------------------------------------------ //
AnimSelfCredit::AnimSelfCredit()
    : 
    Entity({0, 0}, 0), // Both of these are unused. Set default values of 0.
    m_framesCounter(0),
    m_lettersCount(0),
    m_state(State::LETTERS_ADDING),
    m_text("A game by Josh Hayden"),
    m_fontSize(40),
    m_spacing(4.0f),
    m_font(GetFontDefault()),

    m_textPos({ 
        static_cast<float>(G_cntrW - 240), 
        static_cast<float>(G_cntrH)
    }),

    m_bgColor({ 30, 30, 30, 255}),
    m_shortDelay(1 * G_frameRate)
{}

bool AnimSelfCredit::isFinished()
{
    return (m_state == State::FINISHED);
}

void AnimSelfCredit::Update()
{ 
    m_framesCounter++;

    switch (m_state)
    {
        // Letters being added on every 3 frames.
        case State::LETTERS_ADDING: {
            if (m_lettersCount < 21) {
                if (m_framesCounter / 3) {
                    m_lettersCount++;
                    m_framesCounter = 0;
                }
            }
            // If done spelling, wait for 1 second, then move to m_state 1.
            else if (m_framesCounter/m_shortDelay) {  
                    m_state = State::LETTERS_REMOVING; 
                    m_framesCounter = 0;
            }
        } break;

        // Letters being removed on every 3 frames.
        case State::LETTERS_REMOVING: {
            if (m_lettersCount > 0) {
                if (m_framesCounter / 3) {
                    m_lettersCount--;
                    m_framesCounter = 0;
                }
            }
            // If done removing letters, wait for 1 second, then move to m_state 2.
            else if (m_framesCounter / m_shortDelay) {
                    m_state = State::CURSOR_BLINKING; 
            }
        } break;

        case State::CURSOR_BLINKING: {
            m_state = State::BLANK_SCREEN_DELAY; 
        } break;

        case State::BLANK_SCREEN_DELAY: {
            m_state = State::FINISHED;
        } break;

        case State::FINISHED: {} break;
    }
}

void AnimSelfCredit::Draw()
{ 
    // Draw a background rectangle.
    DrawRectangle(G_cntrW - 300, G_cntrH - 30, 600, 100, m_bgColor);
    switch (m_state)
    {
        // Letters being added on every 2 frames.
        case State::LETTERS_ADDING: 
        case State::LETTERS_REMOVING: { 
            float x = m_textPos.x;
            float y = m_textPos.y;

            // Draw every character in 'text' sequentially, drawing a terminal cursor on the
            // last letter.
            for (int i = 0; i < m_lettersCount; i++) {
                char c = m_text.c_str()[i];
                char s[2] = { c, '\0' };

                Vector2 charSize = MeasureTextEx(m_font, s, m_fontSize, m_spacing);

                bool isLast = (i == m_lettersCount - 1);

                if (isLast) {
                    DrawRectangle(
                        static_cast<int>(x), 
                        static_cast<int>(y), 
                        static_cast<int>(charSize.x), 
                        m_fontSize, 
                        DARKBLUE
                    );
                }

                DrawTextEx(m_font, s, { x, y }, m_fontSize, m_spacing, isLast ? WHITE : SKYBLUE);
                x += charSize.x + m_spacing;
            }
        } break;

        case State::CURSOR_BLINKING:
        case State::BLANK_SCREEN_DELAY: 
        case State::FINISHED: {
            return;
        } break;
    }
}
