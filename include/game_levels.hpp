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

using BlinkEngine::Level;
using BlinkEngine::Label;
using BlinkEngine::Button;
using BlinkEngine::AnimRaylib;
using BlinkEngine::AnimSelfCredit;

// Standard library.
#include <string>

using std::string;

class LevelAnimRaylib : public BlinkEngine::Level
{
    public:
        LevelAnimRaylib();
        void Update() override;

    private:
        AnimRaylib* m_animation;
};

class LevelAnimSelfCredit : public BlinkEngine::Level
{
    public:
        LevelAnimSelfCredit();
        void Update() override;

    private:
        AnimSelfCredit* m_animation;
};

class LevelTitle : public BlinkEngine::Level
{
    public:
        LevelTitle();
        void Update() override;

    private:
        const Color m_aquamarine;
        Button* m_playButton;

        class GameTitleText
        {
            public:
                Text* textPtr;

                float currentScale;

                static constexpr float scaleIncr = 0.05;
                static constexpr float maxScale = 1.2;
                static constexpr float minScale = 1.0;

                static constexpr float initialRotation = 0.0;
                static constexpr float rotationSpeed = 5.0;
                static constexpr float rotationDepth = 2.5;

        };
        GameTitleText m_gameTitleText;
};

class LevelLose : public BlinkEngine::Level
{
    public:
        LevelLose();
        void Update() override;

    private:
        Button* m_restartButton;
};

class Level1 : public BlinkEngine::Level
{
    public:
        Level1();
        void Update() override;

    private:
        Button* m_correctAnswer;
};

class Level2 : public BlinkEngine::Level
{
    public:
        Level2(); 
        void Update() override;

    private:
        Button* m_correctAnswer;
};

class Level3 : public BlinkEngine::Level
{
    public:
        Level3(); 
        void Update() override;

    private:
        class CorrectAnswer
        {
            public:
                Button* buttonPtr;

                float currentScale;

                static constexpr float scaleUpIncr = 0.05;
                static constexpr float scaleDownIncr = 0.10;
                static constexpr float maxScale = 2.5;
                static constexpr float minScale = 1.0;
        };
        CorrectAnswer m_correctAnswer;
};

class Level4 : public BlinkEngine::Level
{
    public:
        Level4(); 
        void Update() override;
};

class Level5 : public BlinkEngine::Level
{
    public:
        Level5(string duration); 
        void Update() override;

    private:
        int m_framesCounter;

        string m_duration; 
        Button* m_timer;
};

class Level6 : public BlinkEngine::Level
{
    public:
        Level6();
        void Update() override;

    private:
        Button* m_buttonInHand;
        Label* m_submitBox;
        Button* m_submitButton;

        string m_correctNumber; 
};

class Level7 : public BlinkEngine::Level
{
    public:
        Level7();
        void Update() override;

    private: 
        Button* m_buttonInHand;
        Label* m_submitBox;
        Button* m_submitButton;

        string m_correctNumber;
};
