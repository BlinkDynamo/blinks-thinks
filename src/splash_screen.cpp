/***********************************************************************************************
*
*   splash_screen.cpp - The library for drawing splash screens.
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

// Raylib.
#include "raylib/raylib.h"

// Source.
#include "splash_screen.hpp"
#include "main.hpp"

// ------------------------------------------------------------------------------------------ //
//                                   Raylib splash screen.                                    //
// ------------------------------------------------------------------------------------------ //
RaylibSplash::RaylibSplash()
{
    this->logoPositionX = (screenWidth / 2) - 128;
    this->logoPositionY = (screenHeight / 2) - 128;

    this->framesCounter = 0;
    this->lettersCount = 0;

    this->topSideRecWidth = 16;
    this->leftSideRecHeight = 16;

    this->bottomSideRecWidth = 16;
    this->rightSideRecHeight = 16;

    this->state = 0;
    this->alpha = 1.0f;
}

bool RaylibSplash::isFinished()
{
    return (state == 4);
}

void RaylibSplash::Update()
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
    // If the skip key is pressed, mark the splash screen as finished.
    if (IsKeyPressed(KEY_ENTER)) {
        state = 4;
    }

    switch (state)
    {
        case (0): {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        } break;

        case (1): {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        } break;

        case (2): {
        bottomSideRecWidth += 4;
        rightSideRecHeight += 4;

        if (bottomSideRecWidth == 256) state = 3;
        } break;

        case (3): { 
            framesCounter++;

            if (framesCounter/12)
            {
                lettersCount++;
                framesCounter = 0;
            }

            if (lettersCount >= 10)
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    state = 4;
                }
            }
        } break;

        case (4): {} break;
    }
}

void RaylibSplash::Draw()
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
    
    switch (state)
    {
        case (0): {
            if ((framesCounter / 15) % 2) {
                DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
            }
        } break;

        case (1): {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
        } break;

        case (2): {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

            DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
        } break;

        case (3): {
            DrawRectangle(
                logoPositionX,
                logoPositionY,
                topSideRecWidth,
                16,
                Fade(BLACK, alpha));

            DrawRectangle(
                logoPositionX,
                logoPositionY + 16,
                16,
                leftSideRecHeight - 32,
                Fade(BLACK, alpha));

            DrawRectangle(
                logoPositionX + 240,
                logoPositionY + 16,
                16,
                rightSideRecHeight - 32,
                Fade(BLACK, alpha));

            DrawRectangle(
                logoPositionX,
                logoPositionY + 240,
                bottomSideRecWidth, 16,
                Fade(BLACK, alpha));

            DrawRectangle(
                GetScreenWidth()/2 - 112,
                GetScreenHeight()/2 - 112,
                224,
                224,
                Fade(RAYWHITE, alpha));

            DrawText(
                TextSubtext("raylib", 0, lettersCount),
                screenWidth/2 - 44,
                screenHeight/2 + 48,
                50,
                Fade(BLACK, alpha));

        } break;

        case (4): {
            return;
        } break;
    }
}

// ------------------------------------------------------------------------------------------ //
//                               Blink Software splash screen.                                //
// ------------------------------------------------------------------------------------------ //
BlinkSoftwareSplash::BlinkSoftwareSplash()
{
    // Position.
    this->logoPositionX = screenWidth/2 - 128;
    this->logoPositionY = screenHeight/2 - 128;

    // Counters.
    this->framesCounter = 0;
    this->lettersCount = 0;

    // State of the animation.
    this->state = State::LETTERS_ADDING;

    // Other.
    this->alpha = 1.0f;
    
    this->shortDelay = 1 * frameRate;
}

bool BlinkSoftwareSplash::isFinished()
{
    return (state == State::FINISHED);
}

void BlinkSoftwareSplash::Update()
{ 
    // If the skip key is pressed, mark the splash screen as finished.
    if (IsKeyPressed(KEY_ENTER)) {
        state = State::FINISHED;
    }

    framesCounter++;

    switch (state)
    {
        // Letters being added on every 3 frames.
        case State::LETTERS_ADDING: {
            if (lettersCount < 15) {
                if (framesCounter / 3) {
                    lettersCount++;
                    framesCounter = 0;
                }
            }
            // If done spelling, wait for 1 second, then move to state 1.
            else if (framesCounter/shortDelay) {  
                    state = State::LETTERS_REMOVING; 
                    framesCounter = 0;
            }
        } break;

        // Letters being removed on every 3 frames.
        case State::LETTERS_REMOVING: {
            if (lettersCount > 0) {
                if (framesCounter / 3) {
                    lettersCount--;
                    framesCounter = 0;
                }
            }
            // If done removing letters, wait for 1 second, then move to state 2.
            else if (framesCounter / shortDelay) {
                    state = State::CURSOR_BLINKING; 
            }
        } break;

        case State::CURSOR_BLINKING: {
            state = State::BLANK_SCREEN_DELAY; 
        } break;

        case State::BLANK_SCREEN_DELAY: {
            state = State::FINISHED;
        } break;

        case State::FINISHED: {} break;
    }
}

void BlinkSoftwareSplash::Draw()
{ 
    ClearBackground((Color){ 30, 30, 30, 255});
    switch (state)
    {
        // Letters being added on every 2 frames.
        case State::LETTERS_ADDING: 
        case State::LETTERS_REMOVING: {
            const char* text = "blink software";
            int fontSize = 50;
            float spacing = 4.0f;
            Vector2 textPos = { 
                static_cast<float>(GetScreenWidth()/2 - 160), 
                static_cast<float>(GetScreenHeight()/2)
            };

            Font font = GetFontDefault(); 

            float x = textPos.x;
            float y = textPos.y;

            // Draw every character in 'text' sequentially, drawing a terminal cursor on the
            // last letter.
            for (int i = 0; i < lettersCount; i++) {
                char c = text[i];
                char s[2] = { c, '\0' };

                Vector2 charSize = MeasureTextEx(font, s, fontSize, spacing);

                bool isLast = (i == lettersCount - 1);

                if (isLast) {
                    DrawRectangle(
                        static_cast<int>(x), 
                        static_cast<int>(y), 
                        static_cast<int>(charSize.x), 
                        fontSize, 
                        DARKBLUE
                    );
                }

                DrawTextEx(font, s, { x, y }, fontSize, spacing, isLast ? WHITE : SKYBLUE);
                x += charSize.x + spacing;
            }
        } break;
        
        case State::CURSOR_BLINKING:
        case State::BLANK_SCREEN_DELAY: 
        case State::FINISHED: {
            return;
        } break;
    }
}
