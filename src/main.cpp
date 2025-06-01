/***********************************************************************************************
*
*   main.cpp - The entry point and program runtime.
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

// Raylib.
#include "raylib.h"

// Source.
#include "main.hpp"
#include "animation.hpp"
#include "background.hpp"
#include "button.hpp"
#include "label.hpp"

// Standard library.
#include <cmath>

// Mouse. These are external variables defined in 'include/main.hpp'.
Vector2 mousePoint = { 0.0f, 0.0f };
bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

int main(void)
{
    // -------------------------------------------------------------------------------------- //
    //                                    Initialization.                                     //
    // -------------------------------------------------------------------------------------- //

    // Tracker for the game screen.
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

    // Colors.
    Color BT_SHADOW = { 15, 15, 15, 200 };
    Color BT_AQUAMARINE = { 75, 255, 205, 255 };

    // Window, Screen, and FPS.
    InitWindow(screenWidth, screenHeight, "Blink's Thinks");
    GameScreen currentScreen = LOADING; 
    SetTargetFPS(frameRate);

    // Audio.
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);
    Music title_theme = LoadMusicStream("res/music/title_theme.ogg");
    PlayMusicStream(title_theme);

    // LOADING.
    AnimSelfCredit LOADING_splashSelfCredit;
    AnimRaylib LOADING_splashRaylib;

    // TITLE.
    Background background(
        screenWidth, 
        screenHeight, 
        GRAY, 
        { 200, 200, 200, 255 }, 
        60, 
        50);

    Label TITLE_textTitle(
        "Blink's Thinks",
        100, 
        BT_AQUAMARINE, 
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 100 });
   
    Button TITLE_buttonPlay = makeUiButton("Play");

    // LEVEL_1.
    Label LEVEL_1_textTitle(
        "Level 1",
        80,
        RAYWHITE,
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 250 });
    
    Label LEVEL_1_textPrompt(
        "What is the greatest number?",
        40,
        RAYWHITE,
        BT_SHADOW, 
        { screenWidthCenter, screenHeightCenter - 150 });

    // Answer choices are all invisible buttons with visible text.
    Button LEVEL_1_choiceOne = makeTextButton(
        "144",
        180,
        LIME,
        { screenWidthCenter - 300, screenHeightCenter + 30 });
    
    Button LEVEL_1_choiceTwo = makeTextButton(
        "3",
        70,
        GOLD,
        { screenWidthCenter - 150, screenHeightCenter + 180 });
    
    Button LEVEL_1_choiceThree = makeTextButton(
        "518",
        60,
        BLUE,
        { screenWidthCenter, screenHeightCenter + 130 });
    
    Button LEVEL_1_choiceFour = makeTextButton(
        "0",
        120,
        PINK,
        { screenWidthCenter + 150, screenHeightCenter + 150 });

    Button LEVEL_1_choiceFive = makeTextButton(
        "2869",
        60,
        VIOLET,
        { screenWidthCenter + 300, screenHeightCenter + 150 });

    // LEVEL_2.
    Label LEVEL_2_textTitle(
        "Level 2",
        80,
        RAYWHITE,
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 250 });
    
    Label LEVEL_2_textPrompt(
        "What is the greatest number?",
        40,
        RAYWHITE,
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 150 });

    // Answer choices are all invisible buttons with visible text.
    Button LEVEL_2_choiceOne = makeTextButton(
        "50",
        180,
        LIME,
        { screenWidthCenter - 300, screenHeightCenter + 30 });
    
    Button LEVEL_2_choiceTwo = makeTextButton(
        "36",
        70,
        GOLD,
        { screenWidthCenter - 150, screenHeightCenter + 180 });
    
    Button LEVEL_2_choiceThree = makeTextButton(
        "11",
        60,
        BLUE,
        { screenWidthCenter, screenHeightCenter + 130 });
    
    Button LEVEL_2_choiceFour = makeTextButton(
        "3",
        120,
        PINK,
        { screenWidthCenter + 150, screenHeightCenter + 150 });
    
    Button LEVEL_2_choiceFive = makeTextButton(
        "4",
        60,
        VIOLET,
        { screenWidthCenter + 300, screenHeightCenter + 150 });
    
    // LEVEL_3.
    Label LEVEL_3_textTitle(
        "Level 3",
        80,
        RAYWHITE,
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 250 });

    Label LEVEL_3_textPrompt(
        "What is the greenest number?",
        40,
        RAYWHITE,
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 150 });

    // Answer choices are all invisible buttons with visible text.
    Button LEVEL_3_choiceOne = makeTextButton(
        "7",
        180,
        LIME,
        { screenWidthCenter - 300, screenHeightCenter + 30 });
    
    Button LEVEL_3_choiceTwo = makeTextButton(
        "39",
        70,
        GOLD,
        { screenWidthCenter - 150, screenHeightCenter + 180 });
    
    Button LEVEL_3_choiceThree = makeTextButton(
        "115",
        60,
        BLUE,
        { screenWidthCenter, screenHeightCenter + 130 });
    
    Button LEVEL_3_choiceFour = makeTextButton(
        "2",
        120,
        PINK,
        { screenWidthCenter + 150, screenHeightCenter + 150 });
    
    Button LEVEL_3_choiceFive = makeTextButton(
        "8051",
        60,
        VIOLET,
        { screenWidthCenter + 300, screenHeightCenter + 150 });

    // LOSE.
    Label LOSE_textTitle(
        "You Lose!",
        80,
        BLACK,
        BT_SHADOW,
        { screenWidthCenter, screenHeightCenter - 100 });
    
    Button LOSE_buttonMenu = makeUiButton("Menu");
    
    // Main Event Loop.
    while (!WindowShouldClose())
    {
        // ---------------------------------------------------------------------------------- //
        //                                      Update.                                       //
        // ---------------------------------------------------------------------------------- //

        // Mouse. Remember, these are externs.
        mousePoint = GetMousePosition();
        mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT); 
        
        // Update the music buffer with new stream data.
        UpdateMusicStream(title_theme);
        
        switch (currentScreen)
        {
            case LOADING:
            {
                // Update the correct splash screen in order of what should be played first.
                if (!LOADING_splashRaylib.isFinished()) {
                        LOADING_splashRaylib.Update();
                }
                else if (!LOADING_splashSelfCredit.isFinished()) {
                        LOADING_splashSelfCredit.Update();
                }
            } break;

            case TITLE:
            { 
                background.Update();
                
                TITLE_buttonPlay.Update();
                if (TITLE_buttonPlay.isPressed()) {
                    currentScreen = LEVEL_1;
                } 
            } break;

            case LEVEL_1:
            {
                background.Update();

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
                background.Update();

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
                background.Update();

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
                background.Update();

                LOSE_buttonMenu.Update();

                if (LOSE_buttonMenu.isPressed()) {
                   currentScreen = TITLE;
                } 
            } break;

            case WIN:
            {} break;

            default: break;
        }

        // ---------------------------------------------------------------------------------- //
        //                                       Draw.                                        //
        // ---------------------------------------------------------------------------------- //
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case LOADING:
            {
                // Play the RayLib animation, along with the Blink Software splash screen.
                if (!LOADING_splashRaylib.isFinished()) {
                    LOADING_splashRaylib.Draw();
                }
                else if (!LOADING_splashSelfCredit.isFinished()) {
                    LOADING_splashSelfCredit.Draw();
                }
                else {
                    currentScreen = TITLE;
                }
            } break;

            case TITLE:
            { 
                background.Draw();

                TITLE_textTitle.drawWobbling(
                    2.0f,
                    7.0f); 

                TITLE_buttonPlay.Draw();
            } break;

            case LEVEL_1:
            {
                    background.Draw();

                    LEVEL_1_textTitle.Draw(); 

                    LEVEL_1_textPrompt.drawWobbling(
                        3.0f,
                        2.0f); 
                
                    LEVEL_1_choiceOne.Draw();
                    LEVEL_1_choiceTwo.Draw();
                    LEVEL_1_choiceThree.Draw();
                    LEVEL_1_choiceFour.Draw();
                    LEVEL_1_choiceFive.Draw();
            } break;

            case LEVEL_2:
            {
                background.Draw();

                LEVEL_2_textTitle.Draw(); 

                LEVEL_2_textPrompt.drawWobbling(
                    3.0f,
                    2.0f); 
            
                LEVEL_2_choiceOne.Draw();
                LEVEL_2_choiceTwo.Draw();
                LEVEL_2_choiceThree.Draw();
                LEVEL_2_choiceFour.Draw();
                LEVEL_2_choiceFive.Draw();
            } break;

            case LEVEL_3:
            {
                background.Draw();

                LEVEL_3_textTitle.Draw(); 

                LEVEL_3_textPrompt.drawWobbling(
                    3.0f,
                    2.0f); 
            
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
                background.Draw();

                LOSE_textTitle.drawWobbling(
                    40.0f,
                    2.0f);

                LOSE_buttonMenu.Draw();
            } break;

            case WIN:
            {} break;

            default: break;
        }

        EndDrawing();
    }

    // ------------------------------------------------------------------------------------------ //
    //                                     De-initialization.                                     //
    // ------------------------------------------------------------------------------------------ //

    // Audio.
    UnloadMusicStream(title_theme);
    CloseAudioDevice();

    // Close window and program exit.
    CloseWindow();
    return 0;
}
