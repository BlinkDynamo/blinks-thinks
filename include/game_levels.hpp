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

class LevelAnimRaylib : public Level
{
    public:
        LevelAnimRaylib();
        void Update() override;

    private:
        AnimRaylib* m_animation;
};

class LevelAnimSelfCredit : public Level
{
    public:
        LevelAnimSelfCredit();
        void Update() override;

    private:
        AnimSelfCredit* m_animation;
};

class LevelTitle : public Level
{
    public:
        LevelTitle();
        void Update() override;

    private:
        const Color m_aquamarine;
        Button* m_playButton;
};

class LevelLose : public Level
{
    public:
        LevelLose();
        void Update() override;

    private:
        Button* m_restartButton;
};

class Level1 : public Level
{
    public:
        Level1();
        void Update() override;

    private:
        Button* m_correctAnswer;
};

class Level2 : public Level
{
    public:
        Level2(); 
        void Update() override;

    private:
        Button* m_correctAnswer;
};

class Level3 : public Level
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

class Level4 : public Level
{
    public:
        Level4(); 
        void Update() override;
};

class Level5 : public Level
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

class Level6 : public Level
{
    public:
        Level6();
        void Update() override;

    private:
        Button* m_buttonInHand;
        Rect* m_submitBox;
        Button* m_submitButton;

        int m_greatestNumber; 
};
