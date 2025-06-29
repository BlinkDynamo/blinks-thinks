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
#include "animation.hpp"
#include "background.hpp"
#include "overlay.hpp"
#include "text.hpp"
#include "label.hpp"
#include "button.hpp"

using BlinkEngine::Text;

// Standard library.
#include <string>
#include <vector>
#include <type_traits>

using std::string;
using std::vector;
using std::is_base_of;

namespace BlinkEngine
{
    class Level
    {
        public:
            Level();

            virtual ~Level();                   // Delete 'm_background', as well as all members
                                                // of 'm_entities', clearing the vector as well.

            virtual void Update();              // Will call the 'Update()' method of each member
                                                // of 'm_entities'. Intended to be overloaded,
                                                // calling itself before adding additional logic.

            virtual void Draw();                // Will call the 'Draw()' method of each member
                                                // of 'm_entities'. It's unlikely any overloading
                                                // is needed that can not already be handled in 
                                                // 'Update()', but the option is there.
          
            // Getters and setters.
            vector<Button*> getButtons() { return m_buttons; }

            // Main entity management method. Takes an unknown 'Entity', asserts its subclass,
            // adds that subclass pointer to 'm_entities', then returns the pointer. All factory
            // methods use this to add the created object to 'm_entities'.
            template <typename T>
            T* addEntity(T* newEntity)
            {
                static_assert(is_base_of<Entity, T>::value, "T must derive from Entity.");

                
                // Insert the new entity in the correct position according to it's layer.
                auto it = m_entities.begin();
                while (it != m_entities.end() && (*it)->getLayer() <= newEntity->getLayer()) {
                    ++it;
                }
                m_entities.insert(it, newEntity); 
                
                // If 'entity' is a button, add it to 'm_buttons' as well. 'm_buttons' does not
                // handle any drawing, so sorting by layer is not relevant or needed.
                if constexpr (is_base_of<Button, T>::value) {
                    m_buttons.push_back(static_cast<Button*>(newEntity));
                }

                return newEntity;
            } 

            // ------------------------------------------------------------------------------ //
            //                                Factory methods.                                //
            //                                                                                //
            //  All of these factory methods are to be used inside level implementation code  //
            //  to create objects that exist within a level. Any of these that are called in  //
            //  a 'Level' constructor will add that created object to 'm_entities'.           //
            //                                                                                //
            // ------------------------------------------------------------------------------ //

            // Create a simple text with a background shadow.
            Text* addSimpleText(string text, float fontSize, Color textColor, Vector2 position,
                                  int layer);

            // Create a centered gray and black UI button with custom text.
            Button* addUiButton(string text);

            // Create a button with no background, appearing to only be a clickable text.
            Button* addTextButton(string text, int fontSize, Color textColor, Vector2 position);

        private: 
            vector<Entity*> m_entities;         // All entities made by factory methods are added
                                                // to here, organized by their parent Entity's
                                                // 'm_layer' in order from least to greatest.

            vector<Button*> m_buttons;          // All buttons made by factory methods are added
                                                // to here.
    };
}
