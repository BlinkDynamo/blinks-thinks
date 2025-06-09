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
        // Constructor and destructor.
        Level();
        virtual ~Level();

        // Core methods.
        virtual void Update();
        virtual void Draw();
      
        // Getters and setters.
        std::vector<Button*> getButtons() { return m_buttons; }
       
        // Core factory methods. 
        Label* makeLabel(const char* text, int fontSize, Color textColor, Color shadowColor, Vector2 position);
        Button* makeButton(Label* label, Color bgColor, Vector2 position, Vector2 size); 
        Button* makeUiButton(const char* text);
        Button* makeTextButton(const char* text, int fontSize, Color textColor, Vector2 position);

    private:
        // Current background of the level.
        Background* m_background;

        // Vectors that contain all level entities of a type (m_entities containing everything).
        std::vector<Entity*> m_entities;
        std::vector<Button*> m_buttons;
};
