/***********************************************************************************************
* 
*   label.hpp - The library for creating and drawing formatted text.
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

class Label : public Entity
{
    public:
        Label(
            const char* text,
            int fontSize,
            Color textColor,
            Color shadowColor,
            Vector2 position); 

        void Update() override;
        void Draw() override;

        void setRotation(float rotation, float speed, float depth) {
            m_rotation = rotation;
            m_rotationSpeed = speed;
            m_rotationDepth = depth;
        }
 
        Color getTextColor() { return m_textColor; }
        void setTextColor(Color textColor) { m_textColor = textColor; }

        Vector2 getTextDim() { return m_textDim; }
        void setTextDim(Vector2 textDim) { m_textDim = textDim; }

    private:
        // Arguments.
        const char* m_text;
        int m_fontSize;
        Color m_textColor;
        Color m_shadowColor;
       
        // Set during construction.
        int m_letterSpacing;
        Vector2 m_textDim;
        Vector2 m_origin;
        Vector2 m_shadowOffset;

        // Rotation.
        float m_rotation;
        float m_rotationSpeed;
        float m_rotationDepth;
};
