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
#include <cassert>
#include <iostream>

#ifndef NDEBUG
    #define GAME_ASSERT(cond, msg) \
        do { \
            if (!(cond)) { \
                std::cerr << "[GAME_ASSERT] Assertion failed: (" #cond ") in" \
                          << " (" << __FILE__ << ":" << __LINE__ << ")\n" \
                          << "[GAME_ASSERT] Message: " << msg << std::endl; \
                std::abort(); \
            } \
        } while (0)
#else
    #define GAME_ASSERT(cond, msg) ((void)0)
#endif

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
            int get_random_value(int min, int max);

            // Returns a vector of unique values within a given range. Optionally exclude a vector of values.
            vector<int> get_random_sequence(size_t count, int min, int max, vector<int> exclude = {});

            // Returns a random Raylib-defined color from an array of colors that brighten well.
            Color get_random_color();

            // Returns a vector of randomized, unique, Raylib-defined colors of size 'count'.
            vector<Color> get_random_color_sequence(size_t count);

            // Checks if the cursor is inside the canvas.
            bool mouse_in_canvas();

            // Getters and setters.
            static const string get_game_version() { return m_game_version; }
            static const string get_game_name() { return m_game_name; }

            static constexpr int get_w() { return m_w; } 
            static constexpr int get_h() { return m_h; }
            static constexpr float get_cw() { return m_cw; }
            static constexpr float get_ch() { return m_ch; }

            static constexpr size_t get_frame_rate() { return m_frame_rate; }

            level* get_current_level() { return m_current_level; }
            void set_current_level(level* level){ m_current_level = level; }

            Music* get_current_music() { return m_current_music; }
            void set_current_music(string track_name, bool looping = true);

            void update_music_mixer();

            void set_current_music_pitch(float pitch) { m_current_music_pitch = pitch; }
            float get_current_music_pitch() { return m_current_music_pitch; }
            
            Sound get_sound_effect(string sound_name) { return m_sound_effects.at(sound_name); }

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

            // The structure to handle fading between two music tracks.
            struct {
                Music* old_music = nullptr;
                Music* new_music = nullptr;
                int steps = 20;
                int current_step = 0;
                bool active = false;
            } m_music_mixer;

            // The pitch that the current song is being played at (normal is 1.0).
            float m_current_music_pitch; 

            // All sounds effects loaded on construction and referenced by their sound names.
            unordered_map<string, Sound> m_sound_effects;

            // The random number engine for the game instance.
            std::default_random_engine m_random_generator;

            // RNG specific constants.
            inline static const vector<Color> m_bright_colors = {GOLD, ORANGE, PINK, RED, LIME, SKYBLUE, PURPLE, VIOLET};
    };
}
