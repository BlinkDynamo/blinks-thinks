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
#include "game_levels.hpp"

// Standard library.
#include <cmath>

int main(void)
{
    // -------------------------------------------------------------------------------------- //
    //                                    Initialization.                                     //
    // -------------------------------------------------------------------------------------- // 

    // Window, Screen, and FPS.
    InitWindow(G_w, G_h, "Blink's Thinks");
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
