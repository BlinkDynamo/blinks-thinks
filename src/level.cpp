/***********************************************************************************************
*
*   level.cpp - The library for creating and drawing formatted text.
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
#include "level.hpp"
#include "label.hpp"
#include "button.hpp"
#include "overlay.hpp"
#include "main.hpp"

// Global level pointer for game implementation.
Level* G_currentLevel = nullptr;

Level::Level()
    :
    m_entities{},
    m_buttons{}
{
    // Create a base simple background for all 'Level' objects for now.
    addEntity(new Background(GRAY, { 200, 200, 200, 255 }, 50));
}

Level::~Level()
{
    // Delete all 'Entity' objects in 'entities', then clear the vector.
    for (Entity* entity : m_entities) {
        delete entity;
    }
    m_entities.clear();

    // Only clearing the vector m_buttons is needed, as all were deleted in the prior step.
    m_buttons.clear();
}

void Level::Update()
{
    // Update each 'Entity' object in 'entities'.
    for (const auto& entity : m_entities) {
        entity->Update();
    }
}

void Level::Draw()
{
    // Draw each 'Entity' object in 'entities'.
    for (const auto& entity : m_entities) {
        entity->Draw();
    }
}

// ------------------------------------------------------------------------------------------ //
//                                      Factory methods.                                      //
// ------------------------------------------------------------------------------------------ //

// Make a clickable UI button with dynamic label and background color at a fixed location.
Button* Level::makeUiButton(string text)
{
    constexpr Vector2 position = { G_cntrW, G_cntrH + 100 };
    constexpr int layer = 0;

    Label* const label = new Label(text, 40, WHITE, { 0, 0, 0, 0 }, position, layer);

    Button* const button = new Button(
        label,
        DARKGRAY,
        position,
        layer,
        {180,60}
    );

    addEntity(button);
    return button;
}

// Make clickable label by creating an invisible button in the shape and size of the label.
Button* Level::makeTextButton(string text, int fontSize, Color textColor, Vector2 position)
{
    constexpr int layer = 0;

    Label* const label = new Label(text, fontSize, textColor, G_shadowColor, position, layer);

    Button* const button = new Button(
        label,
        { 0, 0, 0, 0 },
        position,
        layer,
        label->getTextDim()
    );
    
    addEntity(button);
    return button;
}
