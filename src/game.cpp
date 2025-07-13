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

using BlinkEngine::Game;

// Standard library.
#include <cmath>

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

Game::Game()
    :
    m_currentMusicPitch(1.0)
{
    // Window, Screen, and FPS.
    InitWindow(m_w, m_h, m_gameName);
    SetTargetFPS(m_frameRate);

    // Setup the audio device.
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);

    // Load all music tracks into 'm_musicTracks'.
    m_musicTracks["title_theme"] = LoadMusicStream("res/music/title_theme.ogg");
    m_musicTracks["no_stopping_now"] = LoadMusicStream("res/music/no_stopping_now.ogg"); 
}

Game::~Game()
{
    // Unload all the music tracks.
    for (const auto& [name, music] : m_musicTracks) {
        UnloadMusicStream(music);
    }

    CloseAudioDevice();
    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        // ---------------------------------------------------------------------------------- //
        //                                      Update.                                       //
        // ---------------------------------------------------------------------------------- //
        if (m_currentMusic != nullptr) UpdateMusicStream(*m_currentMusic);
        if (m_currentLevel != nullptr) m_currentLevel->Update();

        // ---------------------------------------------------------------------------------- //
        //                                       Draw.                                        //
        // ---------------------------------------------------------------------------------- //
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (m_currentLevel != nullptr) m_currentLevel->Draw();

        EndDrawing();
    }
}
