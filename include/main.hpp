/***********************************************************************************************
*
*   main.hpp - The entry point and program runtime.
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

// Standard library.
#include <cstddef>

// Resolution and framerate.
constexpr int screenWidth = 900;
constexpr int screenHeight = 600;
constexpr float screenWidthCenter = screenWidth / 2.0f;
constexpr float screenHeightCenter = screenHeight / 2.0f;
constexpr size_t frameRate = 60;

// Mouse.
extern Vector2 mousePoint;
extern bool mousePressed;
