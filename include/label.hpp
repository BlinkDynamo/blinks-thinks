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

// Standard library.
#include <string>

using std::string;

class Label : public Entity
{
    public:
        Label(
            string text,
            float fontSize,
            Color textColor,
            Color shadowColor,
            Vector2 position); 

        void Update() override;
        void Draw() override;

        // Getters and setters.
        void setRotation(float rotation, float speed, float depth) {
            m_rotation = rotation;
            m_rotationSpeed = speed;
            m_rotationDepth = depth;
        }

        string getText() { return m_text; }
        void setText(string text) { m_text = text; }

        Color getTextColor() { return m_textColor; }
        void setTextColor(Color textColor) { m_textColor = textColor; }

        Vector2 getTextDim() { return m_textDim; }
        void setTextDim(Vector2 textDim) { m_textDim = textDim; }

        int getFontSize() { return m_baseFontSize; }
        void setFontSize(int fontSize) { m_baseFontSize = fontSize; }

        void setScale(float scale) { m_scale = scale; }

    private:
        string m_text;             // The text that will be displayed.
                                        
        float m_scale;                  // The scaling factor that should be applied to the
                                        // original font size.
                                        
        float m_baseFontSize;           // The size that the text is initially (unscaled).
                                        
        float m_scaledFontSize;         // The size that the text is after scaling is applied.
                                        
        Color m_textColor;              // The color that the text will be displayed.
                                        
        Color m_shadowColor;            // The color that the duplicated, offset text behind
                                        // the main text will be.
                                        
        int m_letterSpacing;            // The pixels of spacing in between letters.
                                        
        Vector2 m_textDim;              // The text's dimensions. Calculated after font size,
                                        // letter spacing, and scaling have all been applied.
                                        
        Vector2 m_origin;               // The horizontal and vertical center of the text.
                                        // Calculated after font size, letter spacing, and
                                        // scaling have all been applied.

        const Vector2 m_shadowOffset;   // The horizontal and vertical offset that the
                                        // duplicated text (shadow) will be drawn at.

        // Rotation algorithm: m_rotation = sin(GetTime() * m_rotationSpeed) * m_rotationDepth

        float m_rotation;               // The rotation of the label (default is 0.0f).
        float m_rotationSpeed;          // The speed the label will be rotated (default is 0.0f).
        float m_rotationDepth;          // The depth the label will rotate (default is 0.0f).
};
