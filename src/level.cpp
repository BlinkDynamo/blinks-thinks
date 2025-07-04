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
#include "text.hpp"
#include "button.hpp"
#include "overlay.hpp"
#include "main.hpp"

using BlinkEngine::Level;
using BlinkEngine::Text;
using BlinkEngine::Button;
using BlinkEngine::Overlay;

Level::Level()
    :
    m_entities{},
    m_buttons{}
{
    // Create a base simple background for all 'Level' objects for now.
    addEntity(new Background(GRAY, { 200, 200, 200, 255 }, 50));

    // Display the current version number in the bottom right.
    addEntity(new Text("v" + G_gameVersion, 20, RAYWHITE, {0, 0, 0, 0}, {G_w - 40, 20}, 1000));
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

// Create a simple text with a background shadow.
Text* Level::addSimpleText(string text, float fontSize, Color textColor, Vector2 position,
                                 int layer)
{
    constexpr Color shadowColor = { 15, 15, 15, 200 };
    Text* const textObj = new Text(text, fontSize, textColor, shadowColor, position, layer);
    addEntity(textObj);
    return textObj;
}

// Make a clickable UI button with dynamic text and background color at a fixed location.
Button* Level::addUiButton(string text)
{
    constexpr Vector2 position = { G_cntrW, G_cntrH + 100 };
    constexpr int layer = 0;

    Text* const textObj = new Text(text, 40, WHITE, { 0, 0, 0, 0 }, position, layer);

    Button* const button = new Button(
        textObj,
        DARKGRAY,
        {180,60},
        position,
        layer
    );

    addEntity(button);
    return button;
}

// Make clickable text by creating an invisible button in the shape and size of the text.
Button* Level::addTextButton(string text, int fontSize, Color textColor, Vector2 position)
{
    constexpr Color shadowColor = { 15, 15, 15, 200 };
    constexpr int layer = 0;

    Text* const textObj = new Text(text, fontSize, textColor, shadowColor, position, layer);

    Button* const button = new Button(
        textObj,
        { 0, 0, 0, 0 },
        textObj->getTextDim(),
        position,
        layer
    );
    
    addEntity(button);
    return button;
}
