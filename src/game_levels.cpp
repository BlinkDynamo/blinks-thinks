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

// Source.
#include "main.hpp"
#include "game_levels.hpp"

// Standard library.
#include <cstdlib>
#include <sstream>

// ------------------------------------------------------------------------------------------ //
//                                     Raylib animation.                                      //
// ------------------------------------------------------------------------------------------ //
LevelAnimRaylib::LevelAnimRaylib()
    :
    m_animation(nullptr)
{
    m_animation = makeAnimRaylib();    
}

void LevelAnimRaylib::Update()
{
    Level::Update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete currentLevel;
        currentLevel = new LevelAnimSelfCredit;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                   Self credit animation.                                   //
// ------------------------------------------------------------------------------------------ //
LevelAnimSelfCredit::LevelAnimSelfCredit()
    :
    m_animation(nullptr)
{
    m_animation = makeAnimSelfCredit();
}

void LevelAnimSelfCredit::Update()
{
    Level::Update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete currentLevel;
        currentLevel = new LevelTitle;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                       Title screen.                                        //
// ------------------------------------------------------------------------------------------ //
LevelTitle::LevelTitle()
    :
    m_playButton(nullptr)
{
    // Non-referenced objects.
    (void)makeLabel("Blink's Thinks", 100, RAYWHITE, BLACK, {screenWidthCenter, screenHeightCenter - 100})
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_playButton = makeUiButton("Play");
}

void LevelTitle::Update()
{
    Level::Update();

    if (m_playButton->isPressed()) {
        delete currentLevel;
        currentLevel = new Level1();
    }
}

// ------------------------------------------------------------------------------------------ //
//                                        Lose screen.                                        //
// ------------------------------------------------------------------------------------------ //
LevelLose::LevelLose()
    :
    m_restartButton(nullptr)
{
// Non-referenced objects.
    (void)makeLabel("Game over!", 100, RED, BLACK, {screenWidthCenter, screenHeightCenter - 100})
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_restartButton = makeUiButton("Restart");
}

void LevelLose::Update()
{
    Level::Update();

    if (m_restartButton->isPressed()) {
        delete currentLevel;
        currentLevel = new Level1();
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 1.                                          //
// ------------------------------------------------------------------------------------------ //
Level1::Level1()
    :
    m_correctAnswer(nullptr)
{
    (void)makeLabel("Level 1", 80, ORANGE, BLACK, {screenWidthCenter, screenHeightCenter - 250});
    (void)makeLabel("What is the largest number?", 40, RAYWHITE, BLACK, {screenWidthCenter, screenHeightCenter - 150})
        ->setRotation(0.0f, 4.0f, 1.5f);

    (void)makeTextButton("144", 60, LIME, {screenWidthCenter - 300, screenHeightCenter});
    (void)makeTextButton("31", 80, GOLD, {screenWidthCenter - 150, screenHeightCenter});
    (void)makeTextButton("50", 100, PINK, {screenWidthCenter, screenHeightCenter});
    (void)makeTextButton("518", 60, BLUE, {screenWidthCenter + 150, screenHeightCenter});
    m_correctAnswer = makeTextButton("2869", 60, VIOLET, {screenWidthCenter + 300, screenHeightCenter}); 
}

void Level1::Update()
{
    // If the correct option is chosen, move on to Level 2.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete currentLevel;
        currentLevel = new Level2();
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete currentLevel;
                currentLevel = new LevelLose();
            }
        }
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 2.                                          //
// ------------------------------------------------------------------------------------------ //
Level2::Level2()
    :
    m_correctAnswer(nullptr)
{
    (void)makeLabel("Level  ", 80, ORANGE, BLACK, {screenWidthCenter - 4, screenHeightCenter - 250});

    m_correctAnswer = makeTextButton("2", 80, ORANGE, {screenWidthCenter + 122, screenHeightCenter - 250});

    (void)makeLabel("What is the smallest number?", 40, RAYWHITE, BLACK,
        {screenWidthCenter, screenHeightCenter - 150})->setRotation(0.0f, 4.0f, 1.5f);
    
    (void)makeTextButton("144", 60, LIME, {screenWidthCenter - 300, screenHeightCenter});
    (void)makeTextButton("31", 80, GOLD, {screenWidthCenter - 150, screenHeightCenter});
    (void)makeTextButton("2869", 60, VIOLET, {screenWidthCenter + 300, screenHeightCenter});
    (void)makeTextButton("50", 100, PINK, {screenWidthCenter, screenHeightCenter});
    (void)makeTextButton("518", 60, BLUE, {screenWidthCenter + 150, screenHeightCenter});
}

void Level2::Update()
{
    // If the correct option is chosen, move on to Level 3.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete currentLevel;
        currentLevel = new Level3();
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete currentLevel;
                currentLevel = new LevelLose();
            }
        }
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 3.                                          //
// ------------------------------------------------------------------------------------------ //
Level3::Level3()
    :
    m_correctAnswer(nullptr),
    // For scaling the correct answer when hovered.
    currentScale(1.00),
    scaleUpIncr(0.05),
    scaleDownIncr(0.10),
    maxScale(2.5),
    minScale(1.00)
{
    (void)makeLabel("Level 3", 80, ORANGE, BLACK, {screenWidthCenter, screenHeightCenter - 250});

    (void)makeLabel("What is the tallest number?", 40, RAYWHITE, BLACK, {screenWidthCenter, screenHeightCenter - 150})
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_correctAnswer = makeTextButton("144", 60, LIME, {screenWidthCenter - 300, screenHeightCenter});
    (void)makeTextButton("31", 80, GOLD, {screenWidthCenter - 150, screenHeightCenter});
    (void)makeTextButton("2869", 60, VIOLET, {screenWidthCenter + 300, screenHeightCenter});
    (void)makeTextButton("50", 100, PINK, {screenWidthCenter, screenHeightCenter});
    (void)makeTextButton("518", 60, BLUE, {screenWidthCenter + 150, screenHeightCenter}); 
}

void Level3::Update()
{
    // If the correct option is hovered, make it grow in scale. Otherwise, make it shrink until
    // it becomes it's normal scale again.
    
    if (m_correctAnswer->isHovered()) {
        if (currentScale < maxScale) {
            currentScale += scaleUpIncr;
            m_correctAnswer->setScale(currentScale);
        }
    } 
    else if (currentScale > minScale) {
            currentScale -= scaleDownIncr;
            m_correctAnswer->setScale(currentScale);
    }
    
    // If the correct option is chosen, move on to Level 4.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete currentLevel;
        currentLevel = new Level4();
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete currentLevel;
                currentLevel = new LevelLose();
            }
        }
    } 
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 4.                                          //
// ------------------------------------------------------------------------------------------ //
Level4::Level4()
{
    (void)makeLabel("Level 4", 80, ORANGE, BLACK, {screenWidthCenter, screenHeightCenter - 250});

    (void)makeLabel("How much time do you want for Level 5?", 40, RAYWHITE, BLACK,
        {screenWidthCenter, screenHeightCenter - 150})->setRotation(0.0f, 4.0f, 1.5f);
    
    (void)makeTextButton("10", 80, LIME, {screenWidthCenter - 300, screenHeightCenter});
    (void)makeTextButton("20", 80, GOLD, {screenWidthCenter - 150, screenHeightCenter});
    (void)makeTextButton("30", 80, VIOLET, {screenWidthCenter + 300, screenHeightCenter});
    (void)makeTextButton("60", 80, PINK, {screenWidthCenter, screenHeightCenter});
    (void)makeTextButton("120", 80, BLUE, {screenWidthCenter + 150, screenHeightCenter});
}

void Level4::Update()
{
    // If the correct option is chosen, move on to Level 3.
    Level::Update();
    
    // Find the button that was pressed, and set the next level's duration to that button's label.
    for (Button* button : getButtons()) {
        if (button->isPressed()) {
            delete currentLevel;
            currentLevel = new Level5(button->getLabel()->getText()); 
        }
    }
}

Level5::Level5(string duration)
    :
    m_timer(nullptr),
    m_framesCounter(0),
    m_duration(duration)
{
    (void)makeLabel("Level 5", 80, ORANGE, BLACK, {screenWidthCenter, screenHeightCenter - 250});

    (void)makeLabel("Survive!", 40, RAYWHITE, BLACK,
        {screenWidthCenter, screenHeightCenter - 150})->setRotation(0.0f, 4.0f, 1.5f);
    
    m_timer = makeLabel(m_duration, 80, LIME, BLACK, {screenWidthCenter, screenHeightCenter}); 
}

void Level5::Update()
{
    Level::Update();

    m_framesCounter++; 
    // Every 1 second, turn the string 'm_duration' into an int, decrement it by 1, then check
    // if it's above 0. If it is, turn it back into a string, then set 'm_timer' to this value. 
    if (m_framesCounter == 60) {
        int i;
        std::istringstream(m_duration) >> i;
        i--;
        if (i > 0) {
            m_framesCounter = 0;

            std::ostringstream oss;
            oss << i;
            m_duration = oss.str();
            m_timer->setText(m_duration);
        }
        else {
            delete currentLevel;
            currentLevel = new LevelTitle();
        }
    } 
}
