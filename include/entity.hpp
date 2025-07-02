/***********************************************************************************************
*
*   entity.hpp - The base class for all game entities.
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

// Raylib.
#include "raylib.h"

namespace BlinkEngine
{
    class Entity {
        public:
            Entity(
                Vector2 position = m_defaultPosition,
                int layer = m_defaultLayer,
                Vector2 speed = m_defaultSpeed
            );
            virtual ~Entity() = default;

            // 'Update()' only does an update of 'm_position', but 'Draw()' is pure virtual.
            virtual void Update();
            virtual void Draw() = 0;

            // Getters and setters.
            virtual Vector2 getPosition() { return m_position; }
            virtual void setPosition(Vector2 position) { m_position = position; }

            virtual int getLayer() { return m_layer; }
            virtual void setLayer(int layer) { m_layer = layer; }

            virtual Vector2 getSpeed() { return m_speed; }
            virtual void setSpeed(Vector2 speed) { m_speed = speed; }

        protected:
            Vector2 m_position;     // The X and Y coordinate position of the entity.

            int m_layer;            // The layer in which the entity resides. This will determine
                                    // draw ordering. Higher numbers are drawn higher, and lower
                                    // numbers are drawn lower.

            Vector2 m_speed;        // The X and Y movement speed per frame of the entity. 

        // Constructor default arguments.
        static constexpr Vector2 m_defaultPosition = {0, 0};
        static constexpr int m_defaultLayer = 0;
        static constexpr Vector2 m_defaultSpeed = {0, 0};
    };
}
