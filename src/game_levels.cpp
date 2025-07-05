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

// ------------------------------------------------------------------------------------------ //
//                                     Raylib animation.                                      //
// ------------------------------------------------------------------------------------------ //
LevelAnimRaylib::LevelAnimRaylib()
    :
    m_animation(nullptr)
{
    m_animation = addEntity(new AnimRaylib()); 
}

void LevelAnimRaylib::Update() {
    Level::Update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new LevelAnimSelfCredit());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                   Self credit animation.                                   //
// ------------------------------------------------------------------------------------------ //
LevelAnimSelfCredit::LevelAnimSelfCredit()
    :
    m_animation(nullptr)
{
    m_animation = addEntity(new AnimSelfCredit());
}

void LevelAnimSelfCredit::Update()
{
    Level::Update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new LevelTitle());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                       Title screen.                                        //
// ------------------------------------------------------------------------------------------ //
LevelTitle::LevelTitle()
    :
    m_aquamarine({ 75, 255, 205, 255 }),
    m_playButton(nullptr)
{
    // Non-referenced objects.
    addSimpleText("Blink's Thinks", 100, m_aquamarine, {Game::getInstance().getCW(), Game::getInstance().getCH() - 100}, 0)
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_playButton = addUiButton("Play");
}

void LevelTitle::Update()
{
    Level::Update();

    if (m_playButton->isPressed()) {
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new Level1());
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
    addSimpleText("Game over!", 100, RED, {Game::getInstance().getCW(), Game::getInstance().getCH() - 100}, 0)
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_restartButton = addUiButton("Restart");
}

void LevelLose::Update()
{
    Level::Update();

    if (m_restartButton->isPressed()) {
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new Level1());
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 1.                                          //
// ------------------------------------------------------------------------------------------ //
Level1::Level1()
    :
    m_correctAnswer(nullptr)
{
    addSimpleText("Level 1", 80, ORANGE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 250}, 0);
    
    addSimpleText("What is the largest number?", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);

    addTextButton("144", 60, LIME, {Game::getInstance().getCW() - 300, Game::getInstance().getCH() + 50});
    addTextButton("31", 80, GOLD, {Game::getInstance().getCW() - 150, Game::getInstance().getCH() + 50});
    addTextButton("50", 100, PINK, {Game::getInstance().getCW(), Game::getInstance().getCH() + 50});
    addTextButton("518", 60, BLUE, {Game::getInstance().getCW() + 150, Game::getInstance().getCH() + 50});
    m_correctAnswer = addTextButton("2869", 60, VIOLET, {Game::getInstance().getCW() + 300, Game::getInstance().getCH() + 50}); 
}

void Level1::Update()
{
    // If the correct option is chosen, move on to Level 2.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new Level2());
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete Game::getInstance().getCurrentLevel();
                Game::getInstance().setCurrentLevel(new LevelLose());
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
    addSimpleText("Level  ", 80, ORANGE, {Game::getInstance().getCW() - 4, Game::getInstance().getCH() - 250}, 0);

    m_correctAnswer = addTextButton("2", 80, ORANGE, {Game::getInstance().getCW() + 122, Game::getInstance().getCH() - 250});

    addSimpleText("What is the smallest number?", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    addTextButton("144", 60, LIME, {Game::getInstance().getCW() - 300, Game::getInstance().getCH() + 50});
    addTextButton("31", 80, GOLD, {Game::getInstance().getCW() - 150, Game::getInstance().getCH() + 50});
    addTextButton("2869", 60, VIOLET, {Game::getInstance().getCW() + 300, Game::getInstance().getCH() + 50});
    addTextButton("50", 100, PINK, {Game::getInstance().getCW(), Game::getInstance().getCH() + 50});
    addTextButton("518", 60, BLUE, {Game::getInstance().getCW() + 150, Game::getInstance().getCH() + 50});
}

void Level2::Update()
{
    // If the correct option is chosen, move on to Level 3.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new Level3());
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete Game::getInstance().getCurrentLevel();
                Game::getInstance().setCurrentLevel(new LevelLose());
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
    addSimpleText("Level 3", 80, ORANGE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 250}, 0);

    addSimpleText("What is the tallest number?", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
    ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_correctAnswer = addTextButton("144", 60, LIME, {Game::getInstance().getCW() - 300, Game::getInstance().getCH() + 50});
    addTextButton("31", 80, GOLD, {Game::getInstance().getCW() - 150, Game::getInstance().getCH() + 50});
    addTextButton("2869", 60, VIOLET, {Game::getInstance().getCW() + 300, Game::getInstance().getCH() + 50});
    addTextButton("50", 100, PINK, {Game::getInstance().getCW(), Game::getInstance().getCH() + 50});
    addTextButton("518", 60, BLUE, {Game::getInstance().getCW() + 150, Game::getInstance().getCH() + 50}); 
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
        delete Game::getInstance().getCurrentLevel();
        Game::getInstance().setCurrentLevel(new Level4());
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete Game::getInstance().getCurrentLevel();
                Game::getInstance().setCurrentLevel(new LevelLose());
            }
        }
    } 
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 4.                                          //
// ------------------------------------------------------------------------------------------ //
Level4::Level4()
{
    addSimpleText("Level 4", 80, ORANGE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 250}, 0);

    addSimpleText("How much time do you want for Level 5?", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    addTextButton("2 seconds", 60, LIME, {Game::getInstance().getCW(), Game::getInstance().getCH() - 50});
    addTextButton("5 seconds", 60, VIOLET, {Game::getInstance().getCW(), Game::getInstance().getCH() + 50});
    addTextButton("10 seconds", 60, BLUE, {Game::getInstance().getCW(), Game::getInstance().getCH() + 150});
}

void Level4::Update()
{
    // If the correct option is chosen, move on to Level 5.
    Level::Update();
    
    // Find the button that was pressed, and set the next level's duration to that button's label.
    for (Button* button : getButtons()) {
        if (button->isPressed()) {
            // Save the chosen button's text to a string, then remove the " seconds" substring.
            string chosenTime = button->getTextObj()->getTextString();
            chosenTime.erase(chosenTime.find(" seconds"), chosenTime.length());

            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new Level5(chosenTime));
        }
    }
}

Level5::Level5(string duration)
    :
    m_framesCounter(0),
    m_timer(nullptr),
    m_duration(duration)
{
    // Main title, information, and countdown timer.
    addSimpleText("Level  ", 80, ORANGE, {Game::getInstance().getCW() - 4, Game::getInstance().getCH() - 250}, 0);

    addTextButton("5", 80, ORANGE, {Game::getInstance().getCW() + 122, Game::getInstance().getCH() - 250});

    addSimpleText("Don't touch any numbers for", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_timer = addTextButton(m_duration, 80, RED, {Game::getInstance().getCW(), Game::getInstance().getCH() - 65});

    addSimpleText("more seconds", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH()}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);

    // All obstacles.
    string longNumOne = "762967340328811348866734234450240332396217777462684390";
    string longNumTwo = "239427620310921174648449330989407894927458570770003111";
    string longNumThree = "230459256723665565627118580006023666643111673444567710";

    addTextButton("68", 120, RED, {Game::getInstance().getCW() - 270, Game::getInstance().getCH() - 500})->setSpeed({0, 12});
    addTextButton(longNumOne, 160, RED, {Game::getInstance().getCW() - 3050, Game::getInstance().getCH() + 250})->setSpeed({3, -1}); 
    addTextButton(longNumTwo, 160, RED, {Game::getInstance().getCW() + 3050, Game::getInstance().getCH() - 230})->setSpeed({-3, 1}); 
    addTextButton("8043001", 120, RED, {Game::getInstance().getCW() - 200, Game::getInstance().getCH() + 1200})->setSpeed({0, -5}); 
    addTextButton("3", 120, RED, {Game::getInstance().getCW() + 600, Game::getInstance().getCH()})->setSpeed({-1, 0});
    addTextButton("762", 160, RED, {Game::getInstance().getCW() - 1300, Game::getInstance().getCH()})->setSpeed({2, 0}); 
    addTextButton("12", 120, RED, {Game::getInstance().getCW() + 1800, Game::getInstance().getCH() - 600})->setSpeed({-8, 4});
    addTextButton("5000006", 120, RED, {Game::getInstance().getCW() + 200, Game::getInstance().getCH() - 3000})->setSpeed({0, 7}); 
    addTextButton("3078", 80, RED, {Game::getInstance().getCW() - 250, Game::getInstance().getCH() - 3100})->setSpeed({0, 7}); 
    addTextButton(longNumThree, 150, RED, {Game::getInstance().getCW() + 4550, Game::getInstance().getCH() - 150})->setSpeed({-4, 0}); 
    addTextButton("7877878447232634", 150, RED, {Game::getInstance().getCW(), Game::getInstance().getCH() + 800})->setSpeed({0, -1}); 
    addTextButton("64", 120, RED, {Game::getInstance().getCW() + 3000, Game::getInstance().getCH() + 700})->setSpeed({-5, -1});
}

void Level5::Update()
{
    Level::Update();

    // Every 60 frames (1 second)...
    m_framesCounter++; 
    if (m_framesCounter == 60) { 
        int i;
        std::istringstream(m_duration) >> i;
        // If there is still time left... 
        if (i > 0) {
            // Reset the frames counter and decrement the time by 1.
            m_framesCounter = 0;
            i--;
            
            // Turn 'i' back into a string, and set the text of m_timer to this.
            std::ostringstream oss;
            oss << i;
            m_duration = oss.str();
            m_timer->getTextObj()->setTextString(m_duration);
        }
        // If there is no time left...
        else { 
            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new Level6());
        } 
    } 
    
    // The lose condition can be this simple because all buttons on level 5 will be numbers.
    for (Button* button : getButtons()) {
        if (button->isHovered()) {
            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new LevelLose());
        }
    }
}

Level6::Level6()
    :
    m_buttonInHand(nullptr),
    m_submitBox(nullptr),
    m_submitButton(nullptr),
    m_correctNumber("86531")
{
    // Main title and instructions.
    addSimpleText("Level  ", 80, ORANGE, {Game::getInstance().getCW() - 4, Game::getInstance().getCH() - 250}, 0);

    addTextButton("6", 80, ORANGE, {Game::getInstance().getCW() + 122, Game::getInstance().getCH() - 250});

    addSimpleText("Fit the greatest number into the box", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);

    // Submit box.
    m_submitBox = addEntity(new Label(BLACK, WHITE, {250, 150}, 6, {Game::getInstance().getCW(), Game::getInstance().getCH() - 25}, -10));

    // Submit button.
    m_submitButton = addUiButton("Submit");

    addTextButton("1", 80, LIME, {Game::getInstance().getCW() - 275, Game::getInstance().getCH()});
    addTextButton("5", 80, GOLD, {Game::getInstance().getCW() - 225, Game::getInstance().getCH() + 175});
    addTextButton("8", 80, VIOLET, {Game::getInstance().getCW() + 225, Game::getInstance().getCH() + 175});
    addTextButton("3", 80, PINK, {Game::getInstance().getCW() + 275, Game::getInstance().getCH()});
}

void Level6::Update()
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

    // If the mouse is pressed and a button is in hand, move it to the cursor's position.    
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
            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new Level7());
        }
        else {
            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new LevelLose());
        }
    }
}

Level7::Level7()
:
    m_buttonInHand(nullptr),
    m_submitBox(nullptr),
    m_submitButton(nullptr),
    m_correctNumber("7")
{ 
    // Main title and instructions.
    addSimpleText("Level  ", 80, ORANGE, {Game::getInstance().getCW() - 4, Game::getInstance().getCH() - 250}, 0);

    addTextButton("7", 80, ORANGE, {Game::getInstance().getCW() + 122, Game::getInstance().getCH() - 250});

    addSimpleText("Put the hungry number in the box", 40, RAYWHITE, {Game::getInstance().getCW(), Game::getInstance().getCH() - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);

    // Submit box.
    m_submitBox = addEntity(new Label(BLACK, WHITE, {250, 150}, 6, {Game::getInstance().getCW(), Game::getInstance().getCH() - 25}, -10));

    // Submit button.
    m_submitButton = addUiButton("Submit");

    addTextButton("5", 80, LIME, {Game::getInstance().getCW() - 275, Game::getInstance().getCH()});
    addTextButton("6", 80, GOLD, {Game::getInstance().getCW() - 225, Game::getInstance().getCH() + 175});
    addTextButton("8", 80, VIOLET, {Game::getInstance().getCW() + 225, Game::getInstance().getCH() + 175});
    addTextButton("10", 80, PINK, {Game::getInstance().getCW() + 275, Game::getInstance().getCH()});
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

    // If the mouse is pressed and a button is in hand, move it to the cursor's position.    
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
            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new Level7());
        }
        else {
            delete Game::getInstance().getCurrentLevel();
            Game::getInstance().setCurrentLevel(new LevelLose());
        }
    }
}
