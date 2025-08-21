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

using engine::game;

// Standard library.
#include <cmath>

game& game::get_instance()
{
    static game instance;
    return instance;
}

game::game()
    :
    m_current_music_pitch(1.0)
{
    // Window, Screen, and FPS.
    InitWindow(m_w, m_h, m_game_name);
    SetTargetFPS(m_frame_rate);

    // Setup the audio device.
    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);

    // Load all music tracks into 'm_music_tracks'.
    m_music_tracks["title_theme"] = LoadMusicStream("res/music/title_theme.ogg");
    m_music_tracks["no_stopping_now"] = LoadMusicStream("res/music/no_stopping_now.ogg"); 
}

game::~game()
{
    // Unload all the music tracks.
    for (const auto& [name, music] : m_music_tracks) {
        UnloadMusicStream(music);
    }

    CloseAudioDevice();
    CloseWindow();
}

void game::run()
{
    while (!WindowShouldClose())
    {
        // ---------------------------------------------------------------------------------- //
        //                                      update.                                       //
        // ---------------------------------------------------------------------------------- //
        if (m_current_music != nullptr) UpdateMusicStream(*m_current_music);
        if (m_current_level != nullptr) m_current_level->update();

        // ---------------------------------------------------------------------------------- //
        //                                       draw.                                        //
        // ---------------------------------------------------------------------------------- //
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (m_current_level != nullptr) m_current_level->draw();

        EndDrawing();
    }
}

int game::random_int_in_range(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_random_generator);
}

Color game::random_bright_color()
{
    constexpr size_t n_bright_colors = 8;
    constexpr Color bright_raylib_colors[n_bright_colors] = {GOLD, ORANGE, PINK, RED, LIME, SKYBLUE, PURPLE, VIOLET};
    return bright_raylib_colors[random_int_in_range(0, n_bright_colors - 1)];
}
