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
#include "animation.hpp"

// Standard library.
#include <string>
#include <vector>

using std::string;
using std::vector;

class Level
{
    public:
        Level();

        virtual ~Level();                   // Delete 'm_background', as well as all members of
                                            // 'm_entities', clearing the vector as well.

        virtual void Update();              // Will call the 'Update()' method of each member
                                            // of 'm_entities'. Intended to be overloaded,
                                            // calling itself before adding additional logic.

        virtual void Draw();                // Will call the 'Draw()' method of each member
                                            // of 'm_entities'. It's unlikely any overloading
                                            // is needed that can not already be handled in 
                                            // 'Update()', but the option is there.
      
        // Getters and setters.
        vector<Button*> getButtons() { return m_buttons; }
       
        // ---------------------------------------------------------------------------------- //
        //                                  Factory methods.                                  //
        //                                                                                    //
        //  All of these factory methods are to be used inside level implementation code to   //
        //  create objects that exist within a level. Any of these that are called in a       //
        //  'Level' constructor will add that created object to 'm_entities'.                 //
        //                                                                                    //
        // ---------------------------------------------------------------------------------- //

        // Wrapper method to the 'AnimRaylib' constructor.
        AnimRaylib* makeAnimRaylib();

        // Wrapper method to the 'AnimSelfCredit' constructor.
        AnimSelfCredit* makeAnimSelfCredit();

        // Wrapper method to the 'Label' constructor.
        Label* makeLabel(string text, int fontSize, Color textColor, Color shadowColor,
                         Vector2 position);

        // Wrapper method to the 'Button' constructor.
        Button* makeButton(Label* label, Color bgColor, Vector2 position, Vector2 size); 

        // Create a centered gray and black UI button with custom text.
        Button* makeUiButton(string text);

        // Create a button with an invisible background, appearing to only be a clickable label.
        Button* makeTextButton(string text, int fontSize, Color textColor, Vector2 position);

    private: 
        Background* m_background;           // Current background of the level. This background
                                            // will have it's 'Update()' and 'Draw()' methods
                                            // called once per frame.

        vector<Entity*> m_entities;    // All entities made by factory methods are added
                                            // to here. All members of this vector will have
                                            // their 'Update()' and 'Draw()' methods called
                                            // once per frame.

        vector<Button*> m_buttons;     // All buttons made by factory methods are added to
                                            // here.
};
