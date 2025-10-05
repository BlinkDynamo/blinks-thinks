/***********************************************************************************************
*
*   button.hpp - The library for creating, drawing, and interacting with buttons.
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
#include "entity_traits.hpp"
#include "text.hpp"

// Standard library.
#include <vector>

using std::vector;

namespace engine
{
    //
    // Base button class.
    //
    class button : public entity {
        public:
            button(
                text* text_obj,
                Color bg_color,
                Vector2 size,
                Vector2 position,
                int layer); 

            ~button();

            void update() override;
            void draw() override;

            bool is_hovered();          // Checks if the mouse is within the button's rectangle.

            bool is_pressed();          // Checks if 'is_hovered()' and the mouse being pressed
                                        // are both true.

            void add_trait(button_trait* trait) { m_traits.push_back(trait); }
            
            // Getters and setters.
            string get_text() { return m_text_obj->get_text_str(); }

            text* get_text_obj() { return m_text_obj; }

            Rectangle get_rectangle() { return m_rectangle; }

            void set_scale(float scale) { m_scale = scale; }

            float get_scale() { return m_scale; }

            void set_sfx_press(Sound sfx_press) { m_sfx_press = sfx_press; }

        private:
            text* m_text_obj;           // The pointer to the text object of the button. The
                                        // button handles updating and drawing it's child text
                                        // within it's own 'update()' and 'draw()' methods.

            Vector2 m_size;             // The area the button's rectangle will occupy. Used to
                                        // calculate 'm_rectangle'.

            Rectangle m_rectangle;      // The rectangle used for most button actions. This is
                                        // calculated from 'm_size', 'm_position', and 'm_scale'.

            Color m_default_text_color; // What color the text object's text should be when not
                                        // hovered.

            Color m_current_text_color; // What color the text object's text should be drawn in
                                        // the current frame.

            Color m_default_bg_color;   // What color the button's background should be when not
                                        // hovered.

            Color m_current_bg_color;   // What color the button's background should be in the
                                        // current frame.

            float m_scale;              // What 'm_rectangle' and the text object's 'm_fontSize'
                                        // are multiplied by.

            Sound m_sfx_press;          // The sound effect played when the button is pressed.

            vector<button_trait*> m_traits; // the storage container to hold all active traits
                                            // attached to the button.
    }; 
}
