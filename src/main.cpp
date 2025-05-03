#include "raylib.h"

#include "splash_screens.hpp"

typedef enum GameScreen { 
    LOADING = 0, 
    TITLE, 
    GAMEPLAY, 
    ENDING 
} GameScreen;

int main(void)
{ 
    const int screenWidth = 900;
    const int screenHeight = 600;
    const int frameRate = 60;
    const int logoScreenDelay = frameRate * 5;

    InitWindow(screenWidth, screenHeight, "Blink's Thinks");

    GameScreen currentScreen = LOADING;

    int framesCounter = 0;
    
    SetTargetFPS(frameRate);

    while (!WindowShouldClose())
    {
        /* ----- Update ----- */
        switch (currentScreen)
        {
            case LOADING:
            {
                framesCounter++;
            } break;

            case TITLE:
            {
                // TODO. 
            } break;

            case GAMEPLAY:
            {
                // TODO. 
            } break;

            case ENDING:
            {
                // TODO. 
            } break;
            default: break;
        }
        
        /* ----- Draw ----- */
        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch(currentScreen)
        {
            case LOADING:
            {
                // Play the elegant RayLib animation, along with the Blink Software splash screen.
                DrawSplashScreenRaylib(screenWidth, screenHeight);
                DrawSplashScreenBlinkSoftware(screenWidth, screenHeight);
                currentScreen = TITLE;
            } break;

            case TITLE:
            {
                // TODO.
            } break;

            case GAMEPLAY:
            {
                // TODO.
            } break;

            case ENDING:
            {
                // TODO.
            } break;

            default: break;
        }

        EndDrawing();
    }

    /* ----- De-Initialization ----- */
    CloseWindow();
    return 0;
}
