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

using BlinkEngine::Level;

// Standard library.
#include <string>

using std::string;

namespace BlinkEngine
{
    class Game
    {
        public:
            static Game& getInstance();

            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;
            Game(Game&&) = delete;
            Game& operator=(Game&&) = delete;

            void Run();

            // Getters and setters.
            static constexpr string getGameVersion() { return m_gameVersion; }
            static constexpr string getGameName() { return m_gameName; }

            static constexpr int getW() { return m_w; } 
            static constexpr int getH() { return m_h; }
            static constexpr float getCW() { return m_cW; }
            static constexpr float getCH() { return m_cH; }

            static constexpr size_t getFrameRate() { return m_frameRate; }

            Level* getCurrentLevel() { return m_currentLevel; }
            void setCurrentLevel(Level* level) { m_currentLevel = level; }

        private: 
            Game(); // Private constructor.
            
            // Version.
            static constexpr string m_gameVersion = "0.0.7";
            static constexpr string m_gameName = "Blink's Thinks";

            // Resolution and framerate.
            static constexpr int m_w = 900;
            static constexpr int m_h = 600;
            static constexpr float m_cW = m_w / 2.0f;
            static constexpr float m_cH = m_h / 2.0f;
            static constexpr size_t m_frameRate = 60;

            // The current level being updated, drawn, and interacted with.
            Level* m_currentLevel;
    };
}
