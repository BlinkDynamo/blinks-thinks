/***********************************************************************************************
*
*   background.hpp - The library for creating and drawing backgrounds.
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

class Background : public Entity
{
    public:
        Background(
            Color darkColor,
            Color lightColor,
            int squareSize);

        void Update() override;
        void Draw() override;

    private:
        // Arguments.
        Color m_darkColor;
        Color m_lightColor;
        int m_squareSize;
};
