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
#include "game.hpp"
#include "level.hpp"
#include "text.hpp"
#include "button.hpp"
#include "overlay.hpp"

using engine::game;
using engine::level;
using engine::text;
using engine::button;
using engine::overlay;

level::level()
    :
    m_entities{},
    m_buttons{},
    m_game(game::get_instance())
{
    // Create a base simple background for all 'level' objects for now.
    add_entity(new background(GRAY, { 200, 200, 200, 255 }, 50));

    string version_and_build_display_str  = ("v" + game::get_game_version());
    float version_and_build_display_spacing;
    #ifndef NDEBUG
        version_and_build_display_str += " debug";
        version_and_build_display_spacing = 74.0f;
    #else
        version_and_build_display_str += " release";
        version_and_build_display_spacing = 84.0f;
    #endif

    // Display the current version number in the bottom right.
    add_entity(
        new text(
            version_and_build_display_str,
            20,
            RAYWHITE,
            {0, 0, 0, 0},
            {game::get_w() - version_and_build_display_spacing, 20},
            1000
        )
    );
}

level::~level()
{
    // Delete all 'entity' objects in 'entities', then clear the vector.
    for (entity* ent : m_entities) {
        delete ent;
    }
    m_entities.clear();

    // Only clearing the vector m_buttons is needed, as all were deleted in the prior step.
    m_buttons.clear();
}

void level::update()
{
    // update each 'entity' object in 'entities'.
    for (const auto& ent : m_entities) {
        ent->update();
    }
}

void level::draw()
{
    // draw each 'entity' object in 'entities'.
    for (const auto& ent : m_entities) {
        ent->draw();
    }
}

// Create a simple text with a background shadow.
text* level::add_simple_text(string text_str, float font_size, Color text_color, Vector2 position,
                                 int layer)
{
    constexpr Color shadow_color = { 15, 15, 15, 200 };
    text* const text_obj = new text(text_str, font_size, text_color, shadow_color, position, layer);
    add_entity(text_obj);
    return text_obj;
}

// Make a clickable UI button with dynamic text and background color at a fixed location.
button* level::add_ui_button(string text_str)
{
    constexpr Vector2 position = { game::get_cw(), game::get_ch() + 100 };
    constexpr int layer = 0;

    text* const text_obj = new text(text_str, 40, WHITE, { 0, 0, 0, 0 }, position, layer);

    button* const btn = new button(
        text_obj,
        DARKGRAY,
        {180,60},
        position,
        layer
    );
    
    btn->set_sfx_press(m_game.get_sound_effect("click"));

    add_entity(btn);
    return btn;
}

// Make clickable text by creating an invisible button in the shape and size of the text.
button* level::add_text_button(string text_str, int font_size, Color text_color, Vector2 position)
{
    constexpr Color shadow_color = { 15, 15, 15, 200 };
    constexpr int layer = 0;

    text* const text_obj = new text(text_str, font_size, text_color, shadow_color, position, layer);

    button* const btn = new button(
        text_obj,
        { 0, 0, 0, 0 },
        text_obj->get_text_dim(),
        position,
        layer
    );

    btn->set_sfx_press(m_game.get_sound_effect("grab"));
    
    add_entity(btn);
    return btn;
}
