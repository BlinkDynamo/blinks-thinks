#include "raylib.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { 
    LOGO_RAYLIB = 0, 
    LOGO_BLINK_SOFTWARE, 
    TITLE, 
    GAMEPLAY, 
    ENDING 
} GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 600;
    const int frameRate = 60;
    const int logoScreenDelay = frameRate * 5;

    InitWindow(screenWidth, screenHeight, "wizard tower");

    GameScreen currentScreen = LOGO_RAYLIB;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames
    
    SetTargetFPS(frameRate);        // Set desired framerate (frames-per-second)

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
            case LOGO_RAYLIB:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                if (framesCounter > logoScreenDelay)
                {
                    currentScreen = LOGO_BLINK_SOFTWARE;
                }
            } break;
            case LOGO_BLINK_SOFTWARE:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                if (framesCounter > logoScreenDelay * 2)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO_RAYLIB:
                {
                    DrawText("RAYLIB", 20, 20, 40, LIGHTGRAY);
                    DrawText("", 290, 220, 20, GRAY);

                } break;
                case LOGO_BLINK_SOFTWARE:
                {
                    DrawText("BLINK SOFTWARE", 20, 20, 40, LIGHTGRAY);
                    DrawText("", 290, 220, 20, GRAY);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("Wizard Tower", 20, 20, 40, DARKGREEN);
                    DrawText("Press 'Enter' or click your mouse to begin.", 120, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
