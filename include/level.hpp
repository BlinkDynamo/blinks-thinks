/***********************************************************************************************
* 
*   level.hpp - The library for creating, loading, and unloading levels. 
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

// Source.
#include "entity.hpp"
#include "button.hpp"
#include "label.hpp"
#include "background.hpp"

// Standard library.
#include <string>
#include <vector>

class Level
{
    public:
        Level();
        virtual ~Level();

        virtual void Update();
        virtual void Draw();

        void makeButton(Label* label, Color bgColor, Vector2 position, Vector2 size);
        void makeLabel(const char* text, int fontSize, Color textColor, Color shadowColor,
                       Vector2 position);
        void makeUiButton(const char* text);
        void makeTextButton(const char* text, int fontSize, Color textColor, Vector2 position);

    private:
        Background* background;
        std::vector<Entity*> entities;
};

// ------------------------------------------------------------------------------------------ //
//                                     Individial levels.                                     //
// ------------------------------------------------------------------------------------------ //
class LevelTitle : public Level
{
    public:
        LevelTitle(); 
        void Update() override;
};

class Level1 : public Level
{
    public:
        Level1(); 
        void Update() override;
};
