#include "raylib.h"


void DrawSplashScreenRaylib(const int screenWidth, const int screenHeight)
/*******************************************************************************************
*
*   Original animation courtesy of Ramon Santamaria. Updated to be called within the draw step.
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
{
    // Initialization
    //--------------------------------------------------------------------------------------

    int logoPositionX = screenWidth/2 - 128;
    int logoPositionY = screenHeight/2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;
    float alpha = 1.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        // Update.
        if (state == 0)                 // State 0: Small box blinking
        {
            framesCounter++;

            if (framesCounter == 120)
            {
                state = 1;
                framesCounter = 0;      // Reset counter... will be used later...
            }
        }
        else if (state == 1)            // State 1: Top and left bars growing
        {
            topSideRecWidth += 4;
            leftSideRecHeight += 4;

            if (topSideRecWidth == 256) state = 2;
        }
        else if (state == 2)            // State 2: Bottom and right bars growing
        {
            bottomSideRecWidth += 4;
            rightSideRecHeight += 4;

            if (bottomSideRecWidth == 256) state = 3;
        }
        else if (state == 3)            // State 3: Letters appearing (one by one)
        {
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
        }
        else if (state == 4)
        {
            continue; // In the original example you would press R here, but in my use case, that is not needed.
        }

        // Draw.
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (state == 0)
        {
            if ((framesCounter/15)%2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
        }
        else if (state == 1)
        {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
        }
        else if (state == 2)
        {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
            DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

            DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
        }
        else if (state == 3)
        {
            DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
            DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

            DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
            DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

            DrawRectangle(GetScreenWidth()/2 - 112, GetScreenHeight()/2 - 112, 224, 224, Fade(RAYWHITE, alpha));

            DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth()/2 - 44, GetScreenHeight()/2 + 48, 50, Fade(BLACK, alpha));
        }
        else if (state == 4)
        {
            return;
        }
    EndDrawing();
    }
}

void DrawSplashScreenBlinkSoftware(const int screenWidth, const int screenHeight)
{
    int logoPositionX = screenWidth/2 - 128;
    int logoPositionY = screenHeight/2 - 128;

    int framesCounter = 0;
    int lettersCount = 0;

    int topSideRecWidth = 16;
    int leftSideRecHeight = 16;

    int bottomSideRecWidth = 16;
    int rightSideRecHeight = 16;

    int state = 0;                  // Tracking animation states (State Machine)
    float alpha = 1.0f;             // Useful for fading

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        framesCounter++;
        switch (state)
        {
            case (0) {
                if (framesCounter/12)       // Every 12 frames, one more letter!
                {
                    lettersCount++;
                    //framesCounter = 0;
                }
            } break;

        if (lettersCount >= 16)     // When all letters have appeared, just fade out everything
        {
            state = 1; 
        }
        
        // Draw step.
    
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (state == 0) {
            DrawText(TextSubtext("Blink Software", 0, lettersCount), GetScreenWidth()/2 - 160, GetScreenHeight()/2, 50, Fade(SKYBLUE, alpha));
        }
        else if (state == 1) {
            continue;
        }
        else if (state == 2)
        {
            return;
        }
        EndDrawing();
    } 
}
