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

class Entity {
    public:
        Entity(Vector2 position, int layer);
        virtual ~Entity() = default;

        virtual void Update() = 0;
        virtual void Draw() = 0;

        virtual Vector2 getPosition() { return m_position; }
        virtual void setPosition(Vector2 position) { m_position = position; }

        virtual int getLayer() { return m_layer; }
        virtual void setLayer(int layer) { m_layer = layer; }

    protected:
        Vector2 m_position;     // The X and Y coordinate position of the entity.

        int m_layer;            // The layer in which the entity resides. This will determine
                                // draw ordering. Higher numbers are drawn higher, and lower
                                // numbers are drawn lower.
}; 
