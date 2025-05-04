#include "raylib.h"

#include "splash_screens.hpp"
#include "backgrounds.hpp"

typedef enum GameScreen { 
    LOADING = 0, 
    TITLE, 
    GAMEPLAY, 
    ENDING 
} GameScreen;

int main(void)
{
    /* ----- Variables ----- */
    
    /* Resolution and framerate. */ 
    const int screenWidth = 900;
    const int screenHeight = 600;
    const int frameRate = 60;
    const int logoScreenDelay = frameRate * 5; 

    int framesCounter = 0;

    /* Mouse */
    Vector2 mousePoint = { 0.0f, 0.0f };

    /* ----- Initialization. ----- */ 
    InitWindow(screenWidth, screenHeight, "Blink's Thinks");
    GameScreen currentScreen = LOADING; 
    SetTargetFPS(frameRate);

    /* ----- Main Event Loop ----- */
    while (!WindowShouldClose())
    {
        /* ----- Update ----- */
        mousePoint = GetMousePosition();
        
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
                // Background.
                {
                    static float scroll = 0.0f;
                    int speed = 30;
                    scroll += speed * GetFrameTime(); 
                    DrawScrollingCheckerboard(screenWidth, screenHeight, SKYBLUE, RAYWHITE, scroll, 50);
                }

                // Title.
                {
                    /* Color, font size, and text. */
                    int fontSize = 100;
                    Color titleColor = LIGHTGRAY;
                    Color titleShadow = { 15, 15, 15, 200 };
                    const char *text = "Blink's Thinks";
                    int textWidth = MeasureText(text, fontSize);

                    /* Position. */
                    int x = (screenWidth - textWidth) / 2;
                    int y = (screenHeight - fontSize) / 2;

                    /* Drawing. */
                    DrawText(text, x, y - 100, fontSize, titleShadow); // Shadow text.
                    DrawText(text, x - 6, y - 106, fontSize, titleColor); // Foreground text.
                }
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
