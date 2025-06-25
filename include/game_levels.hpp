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

#pragma once

// Source.
#include "level.hpp"

// Standard library.
#include <string>

using std::string;

// Global level pointer for game implementation.
extern Level* G_currentLevel;

// ------------------------------------------------------------------------------------------ //
//                                GameLevel class definition.                                 //
// ------------------------------------------------------------------------------------------ //
class GameLevel : public Level
{
    public:
        // ---------------------------------------------------------------------------------- //
        //                                  Factory methods.                                  //
        //                                                                                    //
        //  All of these factory methods are to be used inside level implementation code to   //
        //  create objects that exist within a level. Any of these that are called in a       //
        //  'Level' constructor will add that created object to 'm_entities'.                 //
        //                                                                                    //
        // ---------------------------------------------------------------------------------- //

        // Create a simple label with a background shadow.
        Label* addSimpleLabel(string text, float fontSize, Color textColor, Vector2 position,
                              int layer);

        // Create a centered gray and black UI button with custom text.
        Button* addUiButton(string text);

        // Create a button with an invisible background, appearing to only be a clickable label.
        Button* addTextButton(string text, int fontSize, Color textColor, Vector2 position);
};

// ------------------------------------------------------------------------------------------ //
//                              Individual GameLevel subclasses.                              //
// ------------------------------------------------------------------------------------------ //
class LevelAnimRaylib : public GameLevel
{
    public:
        LevelAnimRaylib();
        void Update() override;

    private:
        AnimRaylib* m_animation;
};

class LevelAnimSelfCredit : public GameLevel
{
    public:
        LevelAnimSelfCredit();
        void Update() override;

    private:
        AnimSelfCredit* m_animation;
};

class LevelTitle : public GameLevel
{
    public:
        LevelTitle();
        void Update() override;

    private:
        const Color m_aquamarine;
        Button* m_playButton;
};

class LevelLose : public GameLevel
{
    public:
        LevelLose();
        void Update() override;

    private:
        Button* m_restartButton;
};

class Level1 : public GameLevel
{
    public:
        Level1();
        void Update() override;

    private:
        Button* m_correctAnswer;
};

class Level2 : public GameLevel
{
    public:
        Level2(); 
        void Update() override;

    private:
        Button* m_correctAnswer;
};

class Level3 : public GameLevel
{
    public:
        Level3(); 
        void Update() override;

    private:
        Button* m_correctAnswer;

        // For scaling the correct answer when hovered.
        float currentScale;
        const float scaleUpIncr;
        const float scaleDownIncr;
        const float maxScale;
        const float minScale;
};

class Level4 : public GameLevel
{
    public:
        Level4(); 
        void Update() override;
};

class Level5 : public GameLevel
{
    public:
        Level5(string duration); 
        void Update() override;

    private:
        int m_framesCounter;

        // Countdown timer.
        Button* m_timer;
        string m_duration; 
};
