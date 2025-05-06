#include "raylib/raylib.h"

#include "blinks-thinks/splash_screens.hpp"
#include "blinks-thinks/backgrounds.hpp"
#include "blinks-thinks/button.hpp"

#include <cmath>

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
    
    /* Window, Screen, and FPS. */ 
    InitWindow(screenWidth, screenHeight, "Blink's Thinks");
    GameScreen currentScreen = LOADING; 
    SetTargetFPS(frameRate);

    /* Splash Screens */    
    BlinkSoftwareSplash blinkSoftwareSplash(screenWidth, screenHeight);
    RaylibSplash raylibSplash(screenWidth, screenHeight);
    
    /* Title Screen */ 
    Background titleScreenBackground(screenWidth, screenHeight, SKYBLUE, RAYWHITE, 60, 50);
    Button playButton("Play", { screenWidth / 2.0f, screenHeight / 2.0f + 100}, {100,40}, RAYWHITE, BLACK);

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
                raylibSplash.Draw();
                blinkSoftwareSplash.Draw();
                currentScreen = TITLE;
            } break;

            case TITLE:
            {
                // Background.
                {
                    static float scroll = 0.0f;
                    scroll += GetFrameTime() * 30.0f;
                    titleScreenBackground.Draw(scroll); 
                }

                // "Blink's Thinks" Title.
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
