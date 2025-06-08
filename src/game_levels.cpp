/***********************************************************************************************
*
*   game_levels.hpp - The implementation of the Level class. All levels used in the game are
*                     defined here.
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
#include "main.hpp"
#include "game_levels.hpp"

// ------------------------------------------------------------------------------------------ //
//                                       Title screen.                                        //
// ------------------------------------------------------------------------------------------ //
LevelTitle::LevelTitle()
{
    // Non-referenced objects.
    (void)makeLabel("Blink's Thinks", 100, RAYWHITE, BLACK,
                    {screenWidthCenter, screenHeightCenter - 100})
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_playButton = makeUiButton("Play");
}

void LevelTitle::Update()
{
    Level::Update();

    if (m_playButton->isPressed()) {
        delete currentLevel;
        currentLevel = new Level1();
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 1.                                          //
// ------------------------------------------------------------------------------------------ //
Level1::Level1()
{
    // Non-referenced objects.
    (void)makeLabel("Level 1", 80, RAYWHITE, BLACK,
                    {screenWidthCenter, screenHeightCenter - 250})
        ->setRotation(0.0f, 5.0f, 1.5f);

    (void)makeLabel("What is the greatest number?", 40, RAYWHITE, BLACK,
                    {screenWidthCenter, screenHeightCenter - 150})
        ->setRotation(0.0f, 4.0f, 1.5f);

    // Referenced objects.
    m_correctAnswer = makeTextButton("144", 180, LIME, {screenWidthCenter - 300, screenHeightCenter + 30}); 
}

void Level1::Update()
{
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete currentLevel;
        currentLevel = new Level2();
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 2.                                          //
// ------------------------------------------------------------------------------------------ //
Level2::Level2()
{
    // Non-referenced objects.
    (void)makeLabel("Level 2", 80, RAYWHITE, BLACK,
                    {screenWidthCenter, screenHeightCenter - 250})
        ->setRotation(0.0f, 5.0f, 1.5f);

    (void)makeLabel("What is the greatest number?", 40, RAYWHITE, BLACK,
                    {screenWidthCenter, screenHeightCenter - 150})
        ->setRotation(0.0f, 4.0f, 1.5f);

    // Referenced objects.
    m_correctAnswer = makeTextButton("144", 180, LIME, {screenWidthCenter - 300, screenHeightCenter + 30}); 
}

void Level2::Update()
{
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete currentLevel;
        currentLevel = new LevelTitle();
    }
}
