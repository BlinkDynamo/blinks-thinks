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
#include "main.hpp"

using std::vector;

Level::Level()
    :
    entities{}
{
    // Create a base simple background for all 'Level' objects for now.
    this->background = new Background(screenWidth, screenHeight, GRAY, { 200, 200, 200, 255 }, 
                                      60, 50);
}

Level::~Level()
{
    // Delete all 'Entity' objects in 'entities', then clear the vector.
    for (Entity* entity : entities) {
        delete entity;
    }
    entities.clear();

    // Delete the 'Background' object.
    delete background;
}

void Level::Update()
{
    // Update the background.
    background->Update();

    // Update each 'Entity' object in 'entities'.
    for (const auto& entity : entities) {
        entity->Update();
    }
}

void Level::Draw()
{
    // Draw the background.
    background->Draw();

    // Draw each 'Entity' object in 'entities'.
    for (const auto& entity : entities) {
        entity->Draw();
    } 
}

void Level::makeButton(Label* label, Color bgColor, Vector2 position, Vector2 size)
{
    entities.push_back(new Button(label, bgColor, position, size));
}

void Level::makeLabel(const char* text, int fontSize, Color textColor, Color shadowColor,
               Vector2 position)
{
    entities.push_back(new Label(text, fontSize, textColor, shadowColor, position));
}

// Make a clickable UI button with dynamic label and background color at a fixed location.
void Level::makeUiButton(const char* text)
{
    Vector2 position = { screenWidthCenter, screenHeightCenter + 100 };

    Label* label = new Label(text, 40, WHITE, { 0, 0, 0, 0 }, position);

    Button* button = new Button(
        label,
        DARKGRAY,
        position,
        {180,60}
    );

    entities.push_back(button);
}

// Make clickable label by creating an invisible button in the shape and size of the label.
void Level::makeTextButton(const char* text, int fontSize, Color textColor, Vector2 position)
{
    Label* label = new Label(text, fontSize, textColor, { 15, 15, 15, 200 }, position);

    Button* button = new Button(
        label,
        { 0, 0, 0, 0 },
        position,
        label->getTextDim()
    );
    
    entities.push_back(button);
}

