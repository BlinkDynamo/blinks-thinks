/***********************************************************************************************
*
*   main - The main entry point and runtime of the program.
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
    /* ----- Variables. ----- */

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

    /* ----- Initialization. ----- */

    /* Window, Screen, and FPS. */
    InitWindow(screenWidth, screenHeight, "Blink's Thinks");
    GameScreen currentScreen = LOADING; 
    SetTargetFPS(frameRate);

    /* LOADING. */
    BlinkSoftwareSplash blinkSoftwareSplash(screenWidth, screenHeight);
    RaylibSplash raylibSplash(screenWidth, screenHeight);

    /* TITLE. */
    Background titleScreenBackground(screenWidth, screenHeight, SKYBLUE, RAYWHITE, 60, 50);
    Button playButton("Play", 30, { screenWidth / 2.0f, screenHeight / 2.0f + 100}, {150,50},
                      LIGHTGRAY, BLACK);

    /* LEVEL_1. */
    Background levelOneBackground(screenWidth, screenHeight, BROWN, BEIGE, 60, 50);

    Text choiceOne(40, 10, RAYWHITE, BLACK, "1");

    /* ----- Main Event Loop ----- */
    while (!WindowShouldClose())
    {
        /* ----- Update. ----- */
        mousePoint = GetMousePosition();
        mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT); 

        switch (currentScreen)
        {
            case LOADING:
            {
                /* TODO. */
            } break;

            case TITLE:
            {
                if (playButton.isPressed(mousePoint, mousePressed)) {
                    currentScreen = LEVEL_1;
                }
            } break;

            case LEVEL_1:
            {
                /* TODO. */
            } break;

            case LEVEL_2:
            {
                /* TODO. */
            } break;

            case LEVEL_3:
            {
                /* TODO. */
            } break;
            
            case LEVEL_4:
            {
                /* TODO. */
            } break;

            case LEVEL_5:
            {
                /* TODO. */
            } break;
            
            case LEVEL_6:
            {
                /* TODO. */
            } break;

            case LEVEL_7:
            {
                /* TODO. */
            } break;

            case LEVEL_8:
            {
                /* TODO. */
            } break;
            
            case LEVEL_9:
            {
                /* TODO. */
            } break;

            case LEVEL_10:
            {
                /* TODO. */
            } break;

            case LOSE:
            {
                /* TODO. */
            } break;

            case WIN:
            {
                /* TODO. */
            } break;

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
                raylibSplash.Draw();
                blinkSoftwareSplash.Draw();
                currentScreen = TITLE;
            } break;

            case TITLE:
            {
                /* Background. */
                {
                    static float scroll = 0.0f;
                    scroll += GetFrameTime() * 30.0f;
                    titleScreenBackground.Draw(scroll); 
                }

                /* "Blink's Thinks" Title. */
                {
                    /* Color, font size, and text. */
                    int fontSize = 100;
                    Color textColor = { 28, 197, 148, 255 };
                    Color shadowColor = { 15, 15, 15, 200 };
                    const char *text = "Blink's Thinks";
                    int textWidth = MeasureText(text, fontSize);

                    /* Position. */
                    Vector2 origin = { textWidth / 2.0f, fontSize / 2.0f };
                    Vector2 position = { screenWidth / 2.0f, screenHeight / 2.0f - 100};

                    /* Rotation */
                    static float rotation = 0.0f;
                    rotation = sin(GetTime()) * 7.0f;

                    Vector2 shadowOffset = { 6.0f, 6.0f };

                    /* Shadow. */
                    DrawTextPro(
                        GetFontDefault(), 
                        text, 
                        (Vector2){ position.x + shadowOffset.x, position.y + shadowOffset.y }, 
                        origin,
                        rotation,
                        fontSize,
                        10,
                        shadowColor
                        );

                    /* Text. */ 
                    DrawTextPro(
                        GetFontDefault(),
                        text,
                        position,
                        origin,
                        rotation,
                        fontSize,
                        10,
                        textColor
                        );
                }

                /* Play button. */
                playButton.Draw(); 
            } break;

            case LEVEL_1:
            {
                /* Background. */
                {
                    static float scroll = 0.0f;
                    scroll += GetFrameTime() * 30.0f;
                    levelOneBackground.Draw(scroll); 
                }

                /* "Level 1" Title. */
                {
                    /* Text, font size, and color. */
                    const char *text = "Level 1";

                    int fontSize = 80;
                    int spacing = 10;
                    Vector2 textDim = MeasureTextEx(GetFontDefault(), text, fontSize, spacing);

                    Color textColor = DARKBROWN;
                    Color shadowColor = { 15, 15, 15, 200 };

                    /* Position. */
                    Vector2 origin = { textDim.x / 2.0f, textDim.y / 2.0f };
                    Vector2 position = { screenWidth / 2.0f, screenHeight / 2.0f - 250};

                    /* Rotation */
                    static float rotation = 0.0f;
                    //rotation = sin(GetTime()) * 3.0f;

                    Vector2 shadowOffset = { 6.0f, 6.0f };

                    /* Shadow. */
                    DrawTextPro(
                        GetFontDefault(), 
                        text, 
                        (Vector2){ position.x + shadowOffset.x, position.y + shadowOffset.y }, 
                        origin,
                        rotation,
                        fontSize,
                        spacing,
                        shadowColor
                        );

                    /* Text. */ 
                    DrawTextPro(
                        GetFontDefault(),
                        text,
                        position,
                        origin,
                        rotation,
                        fontSize,
                        spacing,
                        textColor
                        );
                }

                /* "What is the largest number?" prompt. */
                {
                    /* Text, font size, and color. */
                    const char *text = "What is the largest number?";

                    int fontSize = 40;
                    int spacing = 10;
                    Vector2 textDim = MeasureTextEx(GetFontDefault(), text, fontSize, spacing);

                    Color textColor = RAYWHITE;
                    Color shadowColor = { 15, 15, 15, 200 };

                    /* Position. */
                    Vector2 origin = { textDim.x / 2.0f, textDim.y / 2.0f };
                    Vector2 position = { screenWidth / 2.0f, screenHeight / 2.0f - 150};

                    /* Rotation */
                    static float rotation = 0.0f;
                    /* rotation = sin(GetTime()) * 3.0f; */

                    Vector2 shadowOffset = { 6.0f, 6.0f };

                    /* Shadow. */
                    DrawTextPro(
                        GetFontDefault(), 
                        text, 
                        (Vector2){ position.x + shadowOffset.x, position.y + shadowOffset.y }, 
                        origin,
                        rotation,
                        fontSize,
                        spacing,
                        shadowColor
                        );

                    /* Text. */ 
                    DrawTextPro(
                        GetFontDefault(),
                        text,
                        position,
                        origin,
                        rotation,
                        fontSize,
                        spacing,
                        textColor
                        );
                }
                
                /* Various numbers. */
                {
                    choiceOne.Draw({ screenWidthCenter, 500 });
                }
            } break;

            case LEVEL_2:
            {
                /* TODO. */
            } break;

            case LEVEL_3:
            {
                /* TODO. */
            } break;

            case LEVEL_4:
            {
                /* TODO. */
            } break;

            case LEVEL_5:
            {
                /* TODO. */
            } break;

            case LEVEL_6:
            {
                /* TODO. */
            } break;

            case LEVEL_7:
            {
                /* TODO. */
            } break;

            case LEVEL_8:
            {
                /* TODO. */
            } break;

            case LEVEL_9:
            {
                /* TODO. */
            } break;

            case LEVEL_10:
            {
                /* TODO. */
            } break;

            case LOSE:
            {
                /* TODO. */
            } break;

            case WIN:
            {
                /* TODO. */
            } break;

            default: break;
        }

        EndDrawing();
    }

    /* ----- De-Initialization. ----- */
    CloseWindow();
    return 0;
}
