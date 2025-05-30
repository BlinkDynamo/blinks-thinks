/***********************************************************************************************
*
*   entity.hpp - The base class for all game entities.
*
*   Copyright (c) 2025 Josh Hayden (@BlinkDynamo)
*
*   Blink's Thinks is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
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
        Entity(Vector2 pos = { 0, 0 });
        virtual ~Entity() = default;

        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual Vector2 getPosition() { return position; }
        virtual void setPosition(Vector2 pos) { position = pos; }

    protected:
        Vector2 position; 
}; 
