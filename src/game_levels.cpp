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

// Title Screen.
LevelTitle::LevelTitle()
{
    makeLabel("Blink's Thinks", 100, RAYWHITE, BLACK,
              {screenWidthCenter, screenHeightCenter - 100}); 
    makeUiButton("Play");
}

void LevelTitle::Update()
{
    Level::Update();

    if (mousePressed) {
        delete currentLevel;
        currentLevel = new Level1();
    }
}

Level1::Level1()
{
    makeLabel("Level 1", 50, RAYWHITE, BLACK,
              {screenWidthCenter, screenHeightCenter - 100});
    //makeUiButton("Level1");
}

void Level1::Update()
{
    Level::Update();
    // TODO.
}

