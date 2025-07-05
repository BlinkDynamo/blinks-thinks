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
#include "game.hpp"
#include "overlay.hpp"

using BlinkEngine::Overlay;
using BlinkEngine::Game;

Overlay::Overlay(Color color, Vector2 position, int layer)
    :
    Entity(position, layer),
    m_color(color)
{}

void Overlay::Update()
{}

void Overlay::Draw()
{
    DrawRectangle(m_position.x, m_position.y, Game::getW(), Game::getH(), m_color);
}
