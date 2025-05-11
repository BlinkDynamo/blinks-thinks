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

#include "main.hpp"
#include "splash_screen.hpp"
#include "background.hpp"
#include "button.hpp"
#include "text.hpp"

#include <cmath>

/* Resolution and framerate. */
const int screenWidth = 900;
const int screenHeight = 600;
const int screenWidthCenter = screenWidth / 2.0f;
const int screenHeightCenter = screenHeight / 2.0f;
const int frameRate = 60;

/* Mouse. These are external variables defined in 'include/main.hpp'. */
Vector2 mousePoint = { 0.0f, 0.0f };
bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

int main(void)
{
    /* ------------------------- Initialization. ------------------------- */ 

    /* Tracker for the game screen. */
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

    /* Colors. */
    Color BT_SHADOW = { 15, 15, 15, 200 };
    Color BT_ANSWERHOVER = { 250, 255, 180, 255 };
    Color BT_AQUAMARINE = { 75, 255, 205, 255 };

    /* Background. */
    float backgroundScroll = 0.0f;

    /* Window, Screen, and FPS. */
    InitWindow(screenWidth, screenHeight, "Blink's Thinks");
    GameScreen currentScreen = LOADING; 
    SetTargetFPS(frameRate);

    /* Audio. */
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);
    Music title_theme = LoadMusicStream("audio/title_theme.ogg");
    PlayMusicStream(title_theme);

    /* ---------- LOADING. ---------- */
    BlinkSoftwareSplash LOADING_splashBlinkSoftware;
    RaylibSplash LOADING_splashRaylib;

    /* ---------- TITLE. ---------- */
    Background TITLE_background(
        screenWidth, 
        screenHeight, 
        GRAY, 
        { 200, 200, 200, 255 }, 
        60, 
        50
    );

    Text TITLE_textTitle(
        "Blink's Thinks",
        100, 
        BT_AQUAMARINE, 
        BT_SHADOW
    );
   
    Text TITLE_buttonPlayText("Play", 40, RAYWHITE, { 0, 0, 0, 0 });
    Button TITLE_buttonPlay(
        TITLE_buttonPlayText,
        BLACK,
        DARKGRAY,
        BT_AQUAMARINE,
        { screenWidthCenter, screenHeightCenter + 100 },
        {180,60}
    );

    /*  ---------- LEVEL_1. ---------- */
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
        BT_SHADOW
    );

    Text LEVEL_1_textPrompt(
        "What is the greatest number?",
        40,
        RAYWHITE,
        BT_SHADOW
    );

    /* Answer choices are all invisible buttons with visible text. */
    Text LEVEL_1_choiceOneText("114", 180, LIME, BT_SHADOW);
    Button LEVEL_1_choiceOne(
        LEVEL_1_choiceOneText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 300, screenHeightCenter + 30 },
        { 220, 155 }
    );

    Text LEVEL_1_choiceTwoText("3", 70, GOLD, BT_SHADOW);
    Button LEVEL_1_choiceTwo(
        LEVEL_1_choiceTwoText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 150, screenHeightCenter + 180 },
        { 55, 70 }
    );

    Text LEVEL_1_choiceThreeText("518", 60, BLUE, BT_SHADOW);
    Button LEVEL_1_choiceThree(
        LEVEL_1_choiceThreeText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter, screenHeightCenter + 130 },
        { 70, 55 }
    );

    Text LEVEL_1_choiceFourText("0", 120, PINK, BT_SHADOW);
    Button LEVEL_1_choiceFour(
        LEVEL_1_choiceFourText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 150, screenHeightCenter + 150 },
        { 75, 100 }
    );

    Text LEVEL_1_choiceFiveText ("2869", 60, VIOLET, BT_SHADOW);
    Button LEVEL_1_choiceFive(
        LEVEL_1_choiceFiveText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 300, screenHeightCenter + 150 },
        {50,50}
    );

    /*  ---------- LEVEL_2. ---------- */
    Background LEVEL_2_background(
        screenWidth,
        screenHeight,
        BROWN,
        BEIGE,
        60,
        50
    );

    Text LEVEL_2_textTitle(
        "Level 2",
        80,
        RAYWHITE,
        BT_SHADOW
    );

    Text LEVEL_2_textPrompt(
        "What is the greatest number?",
        40,
        RAYWHITE,
        BT_SHADOW
    );

    /* Answer choices are all invisible buttons with visible text. */
    Text LEVEL_2_choiceOneText("50", 180, LIME, BT_SHADOW);
    Button LEVEL_2_choiceOne(
        LEVEL_2_choiceOneText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 300, screenHeightCenter + 30 },
        { 220, 155 }
    );

    Text LEVEL_2_choiceTwoText("36", 70, GOLD, BT_SHADOW);
    Button LEVEL_2_choiceTwo(
        LEVEL_2_choiceTwoText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 150, screenHeightCenter + 180 },
        { 55, 70 }
    );

    Text LEVEL_2_choiceThreeText("11", 60, BLUE, BT_SHADOW);
    Button LEVEL_2_choiceThree(
        LEVEL_2_choiceThreeText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter, screenHeightCenter + 130 },
        { 70, 55 }
    );

    Text LEVEL_2_choiceFourText("3", 120, PINK, BT_SHADOW);
    Button LEVEL_2_choiceFour(
        LEVEL_2_choiceFourText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 150, screenHeightCenter + 150 },
        { 75, 100 }
    );

    Text LEVEL_2_choiceFiveText ("4", 60, VIOLET, BT_SHADOW);
    Button LEVEL_2_choiceFive(
        LEVEL_2_choiceFiveText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 300, screenHeightCenter + 150 },
        {50,50}
    );

    /*  ---------- LEVEL_3. ---------- */
    Background LEVEL_3_background(
        screenWidth,
        screenHeight,
        BROWN,
        BEIGE,
        60,
        50
    );

    Text LEVEL_3_textTitle(
        "Level 3",
        80,
        RAYWHITE,
        BT_SHADOW
    );

    Text LEVEL_3_textPrompt(
        "What is the greenest number?",
        40,
        RAYWHITE,
        BT_SHADOW
    );

    /* Answer choices are all invisible buttons with visible text. */
    Text LEVEL_3_choiceOneText("7", 180, LIME, BT_SHADOW);
    Button LEVEL_3_choiceOne(
        LEVEL_3_choiceOneText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 300, screenHeightCenter + 30 },
        { 220, 155 }
    );

    Text LEVEL_3_choiceTwoText("39", 70, GOLD, BT_SHADOW);
    Button LEVEL_3_choiceTwo(
        LEVEL_3_choiceTwoText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter - 150, screenHeightCenter + 180 },
        { 55, 70 }
    );

    Text LEVEL_3_choiceThreeText("115", 60, BLUE, BT_SHADOW);
    Button LEVEL_3_choiceThree(
        LEVEL_3_choiceThreeText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter, screenHeightCenter + 130 },
        { 70, 55 }
    );

    Text LEVEL_3_choiceFourText("2", 120, PINK, BT_SHADOW);
    Button LEVEL_3_choiceFour(
        LEVEL_3_choiceFourText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 150, screenHeightCenter + 150 },
        { 75, 100 }
    );

    Text LEVEL_3_choiceFiveText ("8051", 60, VIOLET, BT_SHADOW);
    Button LEVEL_3_choiceFive(
        LEVEL_3_choiceFiveText,
        BT_ANSWERHOVER,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { screenWidthCenter + 300, screenHeightCenter + 150 },
        {50,50}
    );

    /*  ---------- LOSE. ---------- */
    Background LOSE_background(
        screenWidth, 
        screenHeight, 
        { 160, 0, 0, 255 }, 
        { 170, 90, 90, 255 }, 
        60, 
        50
    );

    Text LOSE_textTitle(
        "You Lose!",
        80, 
        BLACK, 
        BT_SHADOW
    );
   
    Text LOSE_buttonRestartText("Menu", 40, BLACK, { 0, 0, 0, 0 });
    Button LOSE_buttonRestart(
        LOSE_buttonRestartText,
        LOSE_buttonRestartText.GetTextColor(),
        GRAY,
        LIGHTGRAY,
        { screenWidthCenter, screenHeightCenter + 100 },
        {180,60}
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
        
        /* Update the music buffer with new stream data. */
        UpdateMusicStream(title_theme);

        switch (currentScreen)
        {
            case LOADING:
            {
                /* Update the correct splash screen in order of what should be played first. */
                if (!LOADING_splashRaylib.isFinished()) {
                        LOADING_splashRaylib.Update();
                }
                else if (!LOADING_splashBlinkSoftware.isFinished()) {
                        LOADING_splashBlinkSoftware.Update();
                }
            } break;

            case TITLE:
            { 
                TITLE_buttonPlay.Update();
                if (TITLE_buttonPlay.isPressed()) {
                    currentScreen = LEVEL_1;
                } 
            } break;

            case LEVEL_1:
            {
                LEVEL_1_choiceOne.Update();
                LEVEL_1_choiceTwo.Update();
                LEVEL_1_choiceThree.Update();
                LEVEL_1_choiceFour.Update();
                LEVEL_1_choiceFive.Update();

                if (mousePressed) {
                    if (LEVEL_1_choiceFive.isPressed()) {
                        currentScreen = LEVEL_2;
                    }
                    else {
                        currentScreen = LOSE;
                    }
                }
            } break;

            case LEVEL_2:
            {
                LEVEL_2_choiceOne.Update();
                LEVEL_2_choiceTwo.Update();
                LEVEL_2_choiceThree.Update();
                LEVEL_2_choiceFour.Update();
                LEVEL_2_choiceFive.Update();

                if (mousePressed) {
                    if (LEVEL_2_choiceOne.isPressed()) {
                        currentScreen = LEVEL_3;
                    }
                    else {
                        currentScreen = LOSE;
                    }
                }
            } break;

            case LEVEL_3:
            {
                LEVEL_3_choiceOne.Update();
                LEVEL_3_choiceTwo.Update();
                LEVEL_3_choiceThree.Update();
                LEVEL_3_choiceFour.Update();
                LEVEL_3_choiceFive.Update();

                if (mousePressed) {
                    if (LEVEL_3_choiceOne.isPressed()) {
                        currentScreen = LEVEL_4;
                    }
                    else {
                        currentScreen = LOSE;
                    }
                }
            } break;
            
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
            {
                if (LOSE_buttonRestart.isPressed()) {
                   currentScreen = TITLE;
                } 
            } break;

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
                if (!LOADING_splashRaylib.isFinished()) {
                    LOADING_splashRaylib.Draw();
                }
                else if (!LOADING_splashBlinkSoftware.isFinished()) {
                    LOADING_splashBlinkSoftware.Draw();
                }
                else {
                    currentScreen = TITLE;
                }
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
            {
                LEVEL_2_background.Draw(backgroundScroll); 
                    
                LEVEL_2_textTitle.DrawStatic({ screenWidthCenter, screenHeightCenter - 250 }); 

                LEVEL_2_textPrompt.DrawWobbling(
                    { screenWidthCenter, screenHeightCenter - 150 },
                    3.0f,
                    2.0f
                ); 
            
                LEVEL_2_choiceOne.Draw();
                LEVEL_2_choiceTwo.Draw();
                LEVEL_2_choiceThree.Draw();
                LEVEL_2_choiceFour.Draw();
                LEVEL_2_choiceFive.Draw();
            } break;

            case LEVEL_3:
            {
                LEVEL_3_background.Draw(backgroundScroll); 
                    
                LEVEL_3_textTitle.DrawStatic({ screenWidthCenter, screenHeightCenter - 250 }); 

                LEVEL_3_textPrompt.DrawWobbling(
                    { screenWidthCenter, screenHeightCenter - 150 },
                    3.0f,
                    2.0f
                ); 
            
                LEVEL_3_choiceOne.Draw();
                LEVEL_3_choiceTwo.Draw();
                LEVEL_3_choiceThree.Draw();
                LEVEL_3_choiceFour.Draw();
                LEVEL_3_choiceFive.Draw();
            } break;

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
            {
                /*  ---------- LOSE. ---------- */
                LOSE_background.Draw(backgroundScroll);

                LOSE_textTitle.DrawWobbling(
                    { screenWidthCenter, screenHeightCenter - 100 },
                    40.0f,
                    2.0f
                );

                LOSE_buttonRestart.Draw();
            } break;

            case WIN:
            {} break;

            default: break;
        }

        EndDrawing();
    }

    /* ----- De-Initialization. ----- */

    /* Audio. */
    UnloadMusicStream(title_theme);
    CloseAudioDevice();

    /* Close window and program exit. */
    CloseWindow();
    return 0;
}
