/***********************************************************************************************
* 
*   game.hpp - The library for creating the monolithic game managing object.
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

#pragma once

// Source.
#include "level.hpp"

using engine::level;

// Standard library.
#include <string>
#include <unordered_map>
#include <random>

using std::string;
using std::unordered_map;

namespace engine
{
    class game
    {
        public:
            static game& get_instance();

            game(const game&) = delete;
            game& operator=(const game&) = delete;
            game(game&&) = delete;
            game& operator=(game&&) = delete;

            // Methods.
            void run();

            // Returns a random int from a defined range inclusively.
            int random_int_in_range(int min, int max);
            
            // Returns a random Raylib-defined color from an array of colors that brighten well.
            Color random_bright_color();

            // Getters and setters.
            static const string get_game_version() { return m_game_version; }
            static const string get_game_name() { return m_game_name; }

            static constexpr int get_w() { return m_w; } 
            static constexpr int get_h() { return m_h; }
            static constexpr float get_cw() { return m_cw; }
            static constexpr float get_ch() { return m_ch; }

            static constexpr size_t get_frame_rate() { return m_frame_rate; }

            level* get_current_level() { return m_current_level; }
            void set_current_level(level* level) { m_current_level = level; }

            Music* get_current_music() { return m_current_music; }
            void set_current_music(Music* music) { m_current_music = music; }

            void set_current_music_by_name(string track_name)
            {
                m_current_music = &m_music_tracks[track_name];
            }

            void set_current_music_pitch(float pitch) { m_current_music_pitch = pitch; }
            float get_current_music_pitch() { return m_current_music_pitch; }

        private:
            game();
            ~game();

            // Version.
            static constexpr const char* m_game_version = "0.0.9";
            static constexpr const char* m_game_name = "Blink's Thinks";

            // Resolution and framerate.
            static constexpr int m_w = 900;
            static constexpr int m_h = 600;
            static constexpr float m_cw = m_w / 2.0f;
            static constexpr float m_ch = m_h / 2.0f;
            static constexpr size_t m_frame_rate = 60;

            // The current level being updated, drawn, and interacted with.
            level* m_current_level;

            // All music tracks loaded on construction and referenced by their track names.
            unordered_map<string, Music> m_music_tracks;

            // The current song being played.
            Music* m_current_music;

            // The pitch that the current song is being played at (normal is 1.0).
            float m_current_music_pitch; 

            // The random number engine for the game instance.
            std::default_random_engine m_random_generator;
    };
}
