/***********************************************************************************************
*
*   main.cpp - The entry point and program runtime.
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

#include "raylib/raylib.h"

#include "blinks-thinks/splash_screen.hpp"
#include "blinks-thinks/background.hpp"
#include "blinks-thinks/button.hpp"
#include "blinks-thinks/text.hpp"

#include <cmath>

typedef enum GameScreen { 
    LOADING = 0, 
    TITLE, 
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    LEVEL_6,
    LEVEL_7,
    LEVEL_8,
    LEVEL_9,
    LEVEL_10,
    LOSE, 
    WIN, 
} GameScreen;

int main(void)
{
    /* ------------------------- Variables. ------------------------- */

    /* Resolution and framerate. */
    const int screenWidth = 900;
    const int screenHeight = 600;
    const int screenWidthCenter = screenWidth / 2.0f;
    const int screenHeightCenter = screenHeight / 2.0f;
    const int frameRate = 60;
    const int logoScreenDelay = frameRate * 5;

    /* Mouse */
    Vector2 mousePoint = { 0.0f, 0.0f };
    bool mousePressed;

    /* Colors. */
    Color SHADOW = { 15, 15, 15, 200 };
    Color ANSWERHOVER = { 250, 255, 180, 255 };

    /* Background. */
    float backgroundScroll = 0.0f;

    /* ------------------------- Initialization. ------------------------- */

    /* Window, Screen, and FPS. */
    InitWindow(screenWidth, screenHeight, "Blink's Thinks");
    GameScreen currentScreen = LOADING; 
    SetTargetFPS(frameRate);

    /* LOADING. */
    BlinkSoftwareSplash LOADING_splashBlinkSoftware(screenWidth, screenHeight);
    RaylibSplash LOADING_splashRaylib(screenWidth, screenHeight);

    /* TITLE. */
    Background TITLE_background(
        screenWidth, 
        screenHeight, 
        SKYBLUE, 
        RAYWHITE, 
        60, 
        50
    );

    Text TITLE_textTitle(
        "Blink's Thinks",
        100, 
        { 28, 197, 148, 255 }, 
        SHADOW
    );
   
    Text TITLE_buttonPlayText("Play", 40, BLACK, { 0, 0, 0, 0 });
    Button TITLE_buttonPlay(
        TITLE_buttonPlayText,
        TITLE_buttonPlayText.GetTextColor(),
        GRAY,
        LIGHTGRAY,
        { screenWidthCenter, screenHeightCenter + 100 },
        {180,60}
    );

    /* LEVEL_1. */
    Background LEVEL_1_background(
        screenWidth,
        screenHeight,
        BROWN,
        BEIGE,
        60,
        50
    );

    Text LEVEL_1_textTitle(
        "Level 1",
        80,
        RAYWHITE,
        SHADOW
    );

    Text LEVEL_1_textPrompt(
        "What is the largest number?",
        40,
        RAYWHITE,
        SHADOW
    );

    /* Answer choices are all invisible buttons with visible text. */
    Text LEVEL_1_choiceOneText("114", 180, GOLD, SHADOW);
    Button LEVEL_1_choiceOne(
        LEVEL_1_choiceOneText,
        ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 300, screenHeightCenter + 30 },
        { 220, 155 }
    );

    Text LEVEL_1_choiceTwoText("3", 70, GOLD, SHADOW);
    Button LEVEL_1_choiceTwo(
        LEVEL_1_choiceTwoText,
        ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 150, screenHeightCenter + 180 },
        { 55, 70 }
    );

    Text LEVEL_1_choiceThreeText("518", 40, GOLD, SHADOW);
    Button LEVEL_1_choiceThree(
        LEVEL_1_choiceThreeText,
        ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter, screenHeightCenter + 130 },
        { 70, 55 }
    );

    Text LEVEL_1_choiceFourText("0", 120, GOLD, SHADOW);
    Button LEVEL_1_choiceFour(
        LEVEL_1_choiceFourText,
        ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 150, screenHeightCenter + 150 },
        { 75, 100 }
    );

    Text LEVEL_1_choiceFiveText ("2869", 50, GOLD, SHADOW);
    Button LEVEL_1_choiceFive(
        LEVEL_1_choiceFiveText,
        ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 300, screenHeightCenter + 150 },
        {50,50}
    );
    
    /* ------------------------- Main Event Loop. ------------------------- */
    while (!WindowShouldClose())
    {
        /* ----- Update. ----- */

        /* Mouse. */
        mousePoint = GetMousePosition();
        mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT); 
        
        /* Background. */
        backgroundScroll += GetFrameTime() * 30.0f;

        switch (currentScreen)
        {
            case LOADING:
            {} break;

            case TITLE:
            {
                if (TITLE_buttonPlay.isPressed()) {
                    currentScreen = LEVEL_1;
                } 
            } break;

            case LEVEL_1:
            {} break;

            case LEVEL_2:
            {} break;

            case LEVEL_3:
            {} break;
            
            case LEVEL_4:
            {} break;

            case LEVEL_5:
            {} break;
            
            case LEVEL_6:
            {} break;

            case LEVEL_7:
            {} break;

            case LEVEL_8:
            {} break;
            
            case LEVEL_9:
            {} break;

            case LEVEL_10:
            {} break;

            case LOSE:
            {} break;

            case WIN:
            {} break;

            default: break;
        }

        /* ----- Draw. ----- */
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case LOADING:
            {
                /* Play the elegant RayLib animation, along with the Blink Software splash screen. */
                LOADING_splashRaylib.Draw();
                LOADING_splashBlinkSoftware.Draw();
                currentScreen = TITLE;
            } break;

            case TITLE:
            { 
                TITLE_background.Draw(backgroundScroll); 

                TITLE_textTitle.DrawWobbling(
                    { screenWidthCenter, screenHeightCenter - 100 },
                    2.0f,
                    7.0f
                ); 

                TITLE_buttonPlay.Draw();
            } break;

            case LEVEL_1:
            {
                    LEVEL_1_background.Draw(backgroundScroll); 
                    
                    LEVEL_1_textTitle.DrawStatic({ screenWidthCenter, screenHeightCenter - 250 }); 

                    LEVEL_1_textPrompt.DrawWobbling(
                        { screenWidthCenter, screenHeightCenter - 150 },
                        3.0f,
                        2.0f
                    ); 
                
                    LEVEL_1_choiceOne.Draw();
                    LEVEL_1_choiceTwo.Draw();
                    LEVEL_1_choiceThree.Draw();
                    LEVEL_1_choiceFour.Draw();
                    LEVEL_1_choiceFive.Draw();
            } break;

            case LEVEL_2:
            {} break;

            case LEVEL_3:
            {} break;

            case LEVEL_4:
            {} break;

            case LEVEL_5:
            {} break;

            case LEVEL_6:
            {} break;

            case LEVEL_7:
            {} break;

            case LEVEL_8:
            {} break;

            case LEVEL_9:
            {} break;

            case LEVEL_10:
            {} break;

            case LOSE:
            {} break;

            case WIN:
            {} break;

            default: break;
        }

        EndDrawing();
    }

    /* ----- De-Initialization. ----- */
    CloseWindow();
    return 0;
}
