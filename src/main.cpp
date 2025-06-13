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

// Source.
#include "main.hpp"
#include "animation.hpp"
#include "background.hpp"
#include "button.hpp"
#include "label.hpp"
#include "level.hpp"

#include "game_levels.hpp"

// Standard library.
#include <cmath>

// Mouse. These are external variables defined in 'include/main.hpp'.
Vector2 G_mousePoint = { 0.0f, 0.0f };
bool G_mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

// Level. Tracks what level should be drawn and updated.
Level* G_currentLevel = nullptr;

int main(void)
{
    // -------------------------------------------------------------------------------------- //
    //                                    Initialization.                                     //
    // -------------------------------------------------------------------------------------- //

    // Colors.
    //Color BT_SHADOW = { 15, 15, 15, 200 };
    //Color BT_AQUAMARINE = { 75, 255, 205, 255 };

    // Window, Screen, and FPS.
    InitWindow(G_screenWidth, G_screenHeight, "Blink's Thinks");
    SetTargetFPS(G_frameRate);

    // If G_currentLevel is not yet set, set it to the Title Screen.
    if (G_currentLevel == nullptr) G_currentLevel = new LevelAnimRaylib();

    // Audio.
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);
    Music title_theme = LoadMusicStream("res/music/title_theme.ogg");
    PlayMusicStream(title_theme); 

    // Main Event Loop.
    while (!WindowShouldClose())
    {
        // ---------------------------------------------------------------------------------- //
        //                                      Update.                                       //
        // ---------------------------------------------------------------------------------- //

        // Mouse. Remember, these are externs.
        G_mousePoint = GetMousePosition();
        G_mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT); 

        // Update the music buffer with new stream data.
        UpdateMusicStream(title_theme);

        G_currentLevel->Update();

        // ---------------------------------------------------------------------------------- //
        //                                       Draw.                                        //
        // ---------------------------------------------------------------------------------- //
        BeginDrawing();

        ClearBackground(RAYWHITE);
        G_currentLevel->Draw();

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
