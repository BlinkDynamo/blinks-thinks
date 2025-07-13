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
#include "game.hpp"
#include "game_levels.hpp"

using BlinkEngine::Game;

// Standard library.
#include <cstdlib>
#include <sstream>
#include <iostream>

// ------------------------------------------------------------------------------------------ //
//                                     Raylib animation.                                      //
// ------------------------------------------------------------------------------------------ //
LevelAnimRaylib::LevelAnimRaylib()
    :
    m_animation(addEntity(new AnimRaylib()))
{
    m_game.setCurrentMusicByName("title_theme"); 
    PlayMusicStream(*m_game.getCurrentMusic());
}

void LevelAnimRaylib::Update() {
    Level::Update(); 

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new LevelTitle());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                   Self credit animation.                                   //
// ------------------------------------------------------------------------------------------ //
LevelAnimSelfCredit::LevelAnimSelfCredit()
    :
    m_animation(addEntity(new AnimSelfCredit()))
{}

void LevelAnimSelfCredit::Update()
{
    Level::Update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new LevelTitle());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                       Title screen.                                        //
// ------------------------------------------------------------------------------------------ //
LevelTitle::LevelTitle()
    :
    m_aquamarine({ 75, 255, 205, 255 }),
    m_playButton(addUiButton("Play")),
    m_gameTitleText{
        .textPtr = addSimpleText("Blink's Thinks", 100, m_aquamarine, {m_game.getCW(), m_game.getCH() - 100}, 0),
        .currentScale = 1.0
    }
{
    this->m_gameTitleText.textPtr->addAnimRotate(0.0f, 5.0f, 2.5f);
}

void LevelTitle::Update()
{
    Level::Update(); 
    
    if (m_playButton->isPressed()) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new Level1());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                        Lose screen.                                        //
// ------------------------------------------------------------------------------------------ //
LevelLose::LevelLose()
    :
    m_restartButton(addUiButton("Restart"))
{
    addSimpleText("Game over!", 100, RED, {m_game.getCW(), m_game.getCH() - 100}, 0)
        ->addAnimRotate(0.0f, 5.0f, 2.5f);
}

void LevelLose::Update()
{
    Level::Update();

    // Hacky solution. Fix this.
    constexpr float epsilon = 0.0001f;
    if (m_game.getCurrentMusicPitch() > 0.8f + epsilon) {
        // Pitch down the current music track.
        SetMusicPitch(*m_game.getCurrentMusic(), m_game.getCurrentMusicPitch());
        m_game.setCurrentMusicPitch(m_game.getCurrentMusicPitch() - 0.01);
    }

    if (m_restartButton->isPressed()) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new Level1());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 1.                                          //
// ------------------------------------------------------------------------------------------ //
Level1::Level1()
    :
    m_correctAnswer(addTextButton("2869", 60, VIOLET, {m_game.getCW() + 300, m_game.getCH() + 50}))
{
    addSimpleText("Level 1", 80, ORANGE, {m_game.getCW(), m_game.getCH() - 250}, 0);
    
    addSimpleText("What is the largest number?", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);

    addTextButton("144", 60, LIME, {m_game.getCW() - 300, m_game.getCH() + 50});
    addTextButton("31", 80, GOLD, {m_game.getCW() - 150, m_game.getCH() + 50});
    addTextButton("50", 100, PINK, {m_game.getCW(), m_game.getCH() + 50});
    addTextButton("518", 60, BLUE, {m_game.getCW() + 150, m_game.getCH() + 50});

    // Set the music track. 
    m_game.setCurrentMusicByName("no_stopping_now");
    PlayMusicStream(*m_game.getCurrentMusic());
}

void Level1::Update()
{
    Level::Update();
    
    // Hacky solution. Fix this.
    constexpr float epsilon = 0.0001f;
    // Pitch back up the current music track if it's below 1.0. Since the player will always
    // restart at level 1, this only needs to be handled here.
    if (m_game.getCurrentMusicPitch() < 1.0 - epsilon) {
        SetMusicPitch(*m_game.getCurrentMusic(), m_game.getCurrentMusicPitch());
        m_game.setCurrentMusicPitch(m_game.getCurrentMusicPitch() + 0.02);
    }

    if (m_correctAnswer->isPressed()) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new Level2());
    }
    else { 
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete m_game.getCurrentLevel();
                m_game.setCurrentLevel(new LevelLose());
            }
        }
    } 
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 2.                                          //
// ------------------------------------------------------------------------------------------ //
Level2::Level2()
    :
    m_correctAnswer(addTextButton("2", 80, ORANGE, {m_game.getCW() + 122, m_game.getCH() - 250}))
{
    addSimpleText("Level  ", 80, ORANGE, {m_game.getCW() - 4, m_game.getCH() - 250}, 0);

    addSimpleText("What is the smallest number?", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);
    
    addTextButton("144", 60, LIME, {m_game.getCW() - 300, m_game.getCH() + 50});
    addTextButton("31", 80, GOLD, {m_game.getCW() - 150, m_game.getCH() + 50});
    addTextButton("2869", 60, VIOLET, {m_game.getCW() + 300, m_game.getCH() + 50});
    addTextButton("50", 100, PINK, {m_game.getCW(), m_game.getCH() + 50});
    addTextButton("518", 60, BLUE, {m_game.getCW() + 150, m_game.getCH() + 50});
}

void Level2::Update()
{
    Level::Update();

    if (m_correctAnswer->isPressed()) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new Level3());
    }
    else { 
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete m_game.getCurrentLevel();
                m_game.setCurrentLevel(new LevelLose());
            }
        }
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 3.                                          //
// ------------------------------------------------------------------------------------------ //
Level3::Level3()
    :
    m_correctAnswer{
        .buttonPtr = addTextButton("144", 60, LIME, {m_game.getCW() - 300, m_game.getCH() + 50}),
        .currentScale = 1.0
    } 
{
    addSimpleText("Level 3", 80, ORANGE, {m_game.getCW(), m_game.getCH() - 250}, 0);

    addSimpleText("What is the tallest number?", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
    ->addAnimRotate(0.0f, 4.0f, 1.5f);
    
    addTextButton("31", 80, GOLD, {m_game.getCW() - 150, m_game.getCH() + 50});
    addTextButton("2869", 60, VIOLET, {m_game.getCW() + 300, m_game.getCH() + 50});
    addTextButton("50", 100, PINK, {m_game.getCW(), m_game.getCH() + 50});
    addTextButton("518", 60, BLUE, {m_game.getCW() + 150, m_game.getCH() + 50}); 
}

void Level3::Update()
{
    // If the correct option is hovered, make it grow in scale. Otherwise, make it shrink until
    // it becomes it's normal scale again. 
    if (m_correctAnswer.buttonPtr->isHovered()) {
        if (m_correctAnswer.currentScale < m_correctAnswer.maxScale) {
            m_correctAnswer.currentScale += m_correctAnswer.scaleUpIncr;
            m_correctAnswer.buttonPtr->setScale(m_correctAnswer.currentScale);
        }
    } 
    else if (m_correctAnswer.currentScale > m_correctAnswer.minScale) {
            m_correctAnswer.currentScale -= m_correctAnswer.scaleDownIncr;
            m_correctAnswer.buttonPtr->setScale(m_correctAnswer.currentScale);
    }
    
    Level::Update();
    if (m_correctAnswer.buttonPtr->isPressed()) {
        delete m_game.getCurrentLevel();
        m_game.setCurrentLevel(new Level4());
    }
    else { 
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete m_game.getCurrentLevel();
                m_game.setCurrentLevel(new LevelLose());
            }
        }
    } 
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 4.                                          //
// ------------------------------------------------------------------------------------------ //
Level4::Level4()
{
    addSimpleText("Level 4", 80, ORANGE, {m_game.getCW(), m_game.getCH() - 250}, 0);

    addSimpleText("How much time do you want for Level 5?", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);

    addTextButton("2 seconds", 60, LIME, {m_game.getCW(), m_game.getCH() - 50});
    addTextButton("5 seconds", 60, VIOLET, {m_game.getCW(), m_game.getCH() + 50});
    addTextButton("10 seconds", 60, BLUE, {m_game.getCW(), m_game.getCH() + 150});
}

void Level4::Update()
{
    Level::Update();

    for (Button* button : getButtons()) {
        if (button->isPressed()) {
            string chosenTime = button->getTextObj()->getTextString();
            chosenTime.erase(chosenTime.find(" seconds"), chosenTime.length());
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new Level5(chosenTime));
        }
    }
}

Level5::Level5(string duration)
    :
    m_framesCounter(0),
    m_duration(duration),
    m_timer(addTextButton(m_duration, 80, RED, {m_game.getCW(), m_game.getCH() - 65}))
{
    // Main title, information, and countdown timer.
    addSimpleText("Level  ", 80, ORANGE, {m_game.getCW() - 4, m_game.getCH() - 250}, 0);

    addTextButton("5", 80, ORANGE, {m_game.getCW() + 122, m_game.getCH() - 250});

    addSimpleText("Don't touch any numbers for", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);

    addSimpleText("more seconds", 40, RAYWHITE, {m_game.getCW(), m_game.getCH()}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);

    // All obstacles.
    string longNumOne = "762967340328811348866734234450240332396217777462684390";
    string longNumTwo = "239427620310921174648449330989407894927458570770003111";
    string longNumThree = "230459256723665565627118580006023666643111673444567710";

    addTextButton("68", 120, RED, {m_game.getCW() - 270, m_game.getCH() - 500})->setSpeed({0, 12});
    addTextButton(longNumOne, 160, RED, {m_game.getCW() - 3050, m_game.getCH() + 250})->setSpeed({3, -1}); 
    addTextButton(longNumTwo, 160, RED, {m_game.getCW() + 3050, m_game.getCH() - 230})->setSpeed({-3, 1}); 
    addTextButton("8043001", 120, RED, {m_game.getCW() - 200, m_game.getCH() + 1200})->setSpeed({0, -5}); 
    addTextButton("3", 120, RED, {m_game.getCW() + 600, m_game.getCH()})->setSpeed({-1, 0});
    addTextButton("762", 160, RED, {m_game.getCW() - 1300, m_game.getCH()})->setSpeed({2, 0}); 
    addTextButton("12", 120, RED, {m_game.getCW() + 1800, m_game.getCH() - 600})->setSpeed({-8, 4});
    addTextButton("5000006", 120, RED, {m_game.getCW() + 200, m_game.getCH() - 3000})->setSpeed({0, 7}); 
    addTextButton("3078", 80, RED, {m_game.getCW() - 250, m_game.getCH() - 3100})->setSpeed({0, 7}); 
    addTextButton(longNumThree, 150, RED, {m_game.getCW() + 4550, m_game.getCH() - 150})->setSpeed({-4, 0}); 
    addTextButton("7877878447232634", 150, RED, {m_game.getCW(), m_game.getCH() + 800})->setSpeed({0, -1}); 
    addTextButton("64", 120, RED, {m_game.getCW() + 3000, m_game.getCH() + 700})->setSpeed({-5, -1});
}

void Level5::Update()
{
    Level::Update();

    // Every 60 frames (1 second)...
    m_framesCounter++; 
    if (m_framesCounter == 60) { 
        int durationAsInt;
        std::istringstream(m_duration) >> durationAsInt;
        // If there is still time left... 
        if (durationAsInt > 0) {
            // Reset the frames counter and decrement the time by 1.
            m_framesCounter = 0;
            --durationAsInt;
            
            // Turn 'i' back into a string, and set the text of m_timer to this.
            std::ostringstream oss;
            oss << durationAsInt;
            m_duration = oss.str();
            m_timer->getTextObj()->setTextString(m_duration);
        }
        // If there is no time left...
        else { 
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new Level6());
        } 
    } 

    // The lose condition can be this simple because all buttons on level 5 will be numbers.
    for (Button* button : getButtons()) {
        if (button->isHovered()) {
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new LevelLose());
        }
    }
}

Level6::Level6()
    :
    m_buttonInHand(nullptr),
    m_submitBox(addEntity(new Label(BLACK, WHITE, {250, 150}, 6, {m_game.getCW(), m_game.getCH() - 25}, -10))),
    m_submitButton(addUiButton("Submit")),
    m_correctNumber("86531")
{
    // Main title and instructions.
    addSimpleText("Level  ", 80, ORANGE, {m_game.getCW() - 4, m_game.getCH() - 250}, 0);

    addTextButton("6", 80, ORANGE, {m_game.getCW() + 122, m_game.getCH() - 250});

    addSimpleText("Fit the greatest number into the box", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);

    addTextButton("1", 80, LIME, {m_game.getCW() - 275, m_game.getCH()});
    addTextButton("5", 80, GOLD, {m_game.getCW() - 225, m_game.getCH() + 175});
    addTextButton("8", 80, VIOLET, {m_game.getCW() + 225, m_game.getCH() + 175});
    addTextButton("3", 80, PINK, {m_game.getCW() + 275, m_game.getCH()});
}

void Level6::Update()
{
    Level::Update();

    // The number-dragging can be this simple because all buttons are numbers except the 'Submit' button.
    for (Button* button : getButtons()) {
        if (button->isPressed() && button != m_submitButton) { 
            m_buttonInHand = button; 
        }
    }

    if (IsMouseButtonDown(0) && m_buttonInHand != nullptr) {
        m_buttonInHand->setPosition(GetMousePosition());
    }
    else {
        m_buttonInHand = nullptr;
    }

    // On submission, add every button inside of the submission box to a vector, then organize
    // their text object's text strings in the same order that they exist spatially. Save this
    // created number to a string and check if it matches 'm_correctNumber'.
    if (m_submitButton->isPressed()) {
        vector<Button*> numbersInBox; // For buttons that are inside of the submission box.
        string finalSubmission; // The final submission to match against 'm_greatestNumber'.
        for (Button* button : getButtons()) {
            if (CheckCollisionRecs(button->getRectangle(), m_submitBox->getRectangle())) {
                auto it = numbersInBox.begin();
                while (it != numbersInBox.end() && (*it)->getPosition().x <= button->getPosition().x) {
                    ++it;
                }
                numbersInBox.insert(it, button);
            }
        }
        for (Button* button : numbersInBox) {
            finalSubmission += button->getTextObj()->getTextString();
        }

        if (finalSubmission == m_correctNumber) {
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new Level7());
        }
        else {
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new LevelLose());
        }
    }
}

Level7::Level7()
:
    m_buttonInHand(nullptr),
    m_submitBox(addEntity(new Label(BLACK, WHITE, {250, 150}, 6, {m_game.getCW(), m_game.getCH() - 25}, -10))),
    m_submitButton(addUiButton("Submit")),
    m_correctNumber("7")
{ 
    addSimpleText("Level  ", 80, ORANGE, {m_game.getCW() - 4, m_game.getCH() - 250}, 0);

    addTextButton("7", 80, ORANGE, {m_game.getCW() + 122, m_game.getCH() - 250});

    addSimpleText("Put the hungry number in the box", 40, RAYWHITE, {m_game.getCW(), m_game.getCH() - 150}, 0)
        ->addAnimRotate(0.0f, 4.0f, 1.5f);

    addTextButton("5", 80, LIME, {m_game.getCW() - 275, m_game.getCH()});
    addTextButton("6", 80, GOLD, {m_game.getCW() - 225, m_game.getCH() + 175});
    addTextButton("8", 80, VIOLET, {m_game.getCW() + 225, m_game.getCH() + 175});
    addTextButton("10", 80, PINK, {m_game.getCW() + 275, m_game.getCH()});
}

void Level7::Update()
{
    Level::Update();

    // The number-dragging can be this simple because all buttons are numbers except the 'Submit' button.
    for (Button* button : getButtons()) {
        if (button->isPressed() && button != m_submitButton) {
            // point 'm_buttonInHand' to the button that was just pressed, setting it back to
            // 'nullptr' if the mouse is released.
            m_buttonInHand = button; 
        }
    }

    if (IsMouseButtonDown(0) && m_buttonInHand != nullptr) {
        m_buttonInHand->setPosition(GetMousePosition());
    }
    else {
        m_buttonInHand = nullptr;
    }

    // On submission, add every button inside of the submission box to a vector, then organize
    // their text object's text strings in the same order that they exist spatially. Save this
    // created number to a string and check if it matches 'm_correctNumber'.
    if (m_submitButton->isPressed()) {
        vector<Button*> numbersInBox; // For buttons that are inside of the submission box.
        string finalSubmission; // The final submission to match against 'm_correctNumber'.
        for (Button* button : getButtons()) {
            if (CheckCollisionRecs(button->getRectangle(), m_submitBox->getRectangle())) {
                auto it = numbersInBox.begin();
                while (it != numbersInBox.end() && (*it)->getPosition().x <= button->getPosition().x) {
                    ++it;
                }
                numbersInBox.insert(it, button);
            }
        } 
        for (Button* button : numbersInBox) {
            finalSubmission += button->getTextObj()->getTextString();
        }
  
        if (finalSubmission == m_correctNumber) {
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new Level7());
        }
        else {
            delete m_game.getCurrentLevel();
            m_game.setCurrentLevel(new LevelLose());
        }
    }
}
