/***********************************************************************************************
*
*   overlay.cpp - The library for creating and drawing overlays.
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
#include "overlay.hpp"
#include "main.hpp"

Overlay::Overlay(Color color)
    :
    Entity({0, 0}), // Set this to 0, 0 for now. Position is unused.
    m_color(color)
{}

void Overlay::Update()
{}

void Overlay::Draw()
{
    DrawRectangle(0, 0, G_screenWidth, G_screenHeight, m_color);
}
