/***********************************************************************************************
* 
*   game.cpp - The library for creating the monolithic game managing object.
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
#include "game.hpp"

// Standard library.
#include <cmath>

using BlinkEngine::Game;

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::Game()
{}

void Game::Run()
{
    // -------------------------------------------------------------------------------------- //
    //                                    Initialization.                                     //
    // -------------------------------------------------------------------------------------- // 

    // Window, Screen, and FPS.
    InitWindow(m_w, m_h, m_gameName);
    SetTargetFPS(m_frameRate);

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

        if (m_currentLevel != nullptr) m_currentLevel->Update();

        // ---------------------------------------------------------------------------------- //
        //                                       Draw.                                        //
        // ---------------------------------------------------------------------------------- //
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (m_currentLevel != nullptr) m_currentLevel->Draw();

        EndDrawing();
    }

    // -------------------------------------------------------------------------------------- //
    //                                     De-initialization.                                 //
    // -------------------------------------------------------------------------------------- //

    // Audio.
    UnloadMusicStream(title_theme);
    CloseAudioDevice();

    // Close window and program exit.
    CloseWindow();
}
