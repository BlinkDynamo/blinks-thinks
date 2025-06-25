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

// Global level pointer for game implementation.
Level* G_currentLevel = nullptr;

// ------------------------------------------------------------------------------------------ //
//                                GameLevel class definitions.                                //
// ------------------------------------------------------------------------------------------ //

// Create a simple label with a background shadow.
Label* GameLevel::addSimpleLabel(string text, float fontSize, Color textColor, Vector2 position,
                                 int layer)
{
    constexpr Color shadowColor = { 15, 15, 15, 200 };
    Label* const label = new Label(text, fontSize, textColor, shadowColor, position, layer);
    addEntity(label);
    return label;
}

// Make a clickable UI button with dynamic label and background color at a fixed location.
Button* GameLevel::addUiButton(string text)
{
    constexpr Vector2 position = { G_cntrW, G_cntrH + 100 };
    constexpr int layer = 0;

    Label* const label = new Label(text, 40, WHITE, { 0, 0, 0, 0 }, position, layer);

    Button* const button = new Button(
        label,
        DARKGRAY,
        position,
        layer,
        {180,60}
    );

    addEntity(button);
    return button;
}

// Make clickable label by creating an invisible button in the shape and size of the label.
Button* GameLevel::addTextButton(string text, int fontSize, Color textColor, Vector2 position)
{
    constexpr Color shadowColor = { 15, 15, 15, 200 };
    constexpr int layer = 0;

    Label* const label = new Label(text, fontSize, textColor, shadowColor, position, layer);

    Button* const button = new Button(
        label,
        { 0, 0, 0, 0 },
        position,
        layer,
        label->getTextDim()
    );
    
    addEntity(button);
    return button;
}

// ------------------------------------------------------------------------------------------ //
//                              Individual GameLevel subclasses.                              //
// ------------------------------------------------------------------------------------------ //


// ------------------------------------------------------------------------------------------ //
//                                     Raylib animation.                                      //
// ------------------------------------------------------------------------------------------ //
LevelAnimRaylib::LevelAnimRaylib()
    :
    m_animation(nullptr)
{
    m_animation = addEntity(new AnimRaylib()); 
}

void LevelAnimRaylib::Update()
{
    Level::Update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete G_currentLevel;
        G_currentLevel = new LevelAnimSelfCredit;
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
        delete G_currentLevel;
        G_currentLevel = new LevelTitle;
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
    addSimpleLabel("Blink's Thinks", 100, m_aquamarine, {G_cntrW, G_cntrH - 100}, 0)
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_playButton = addUiButton("Play");
}

void LevelTitle::Update()
{
    Level::Update();

    if (m_playButton->isPressed()) {
        delete G_currentLevel;
        G_currentLevel = new Level1();
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
    addSimpleLabel("Game over!", 100, RED, {G_cntrW, G_cntrH - 100}, 0)
        ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_restartButton = addUiButton("Restart");
}

void LevelLose::Update()
{
    Level::Update();

    if (m_restartButton->isPressed()) {
        delete G_currentLevel;
        G_currentLevel = new Level1();
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 1.                                          //
// ------------------------------------------------------------------------------------------ //
Level1::Level1()
    :
    m_correctAnswer(nullptr)
{
    addSimpleLabel("Level 1", 80, ORANGE, {G_cntrW, G_cntrH - 250}, 0);
    
    addSimpleLabel("What is the largest number?", 40, RAYWHITE, {G_cntrW, G_cntrH - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);

    addTextButton("144", 60, LIME, {G_cntrW - 300, G_cntrH + 50});
    addTextButton("31", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    addTextButton("50", 100, PINK, {G_cntrW, G_cntrH + 50});
    addTextButton("518", 60, BLUE, {G_cntrW + 150, G_cntrH + 50});
    m_correctAnswer = addTextButton("2869", 60, VIOLET, {G_cntrW + 300, G_cntrH + 50}); 
}

void Level1::Update()
{
    // If the correct option is chosen, move on to Level 2.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete G_currentLevel;
        G_currentLevel = new Level2();
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete G_currentLevel;
                G_currentLevel = new LevelLose();
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
    addSimpleLabel("Level  ", 80, ORANGE, {G_cntrW - 4, G_cntrH - 250}, 0);

    m_correctAnswer = addTextButton("2", 80, ORANGE, {G_cntrW + 122, G_cntrH - 250});

    addSimpleLabel("What is the smallest number?", 40, RAYWHITE, {G_cntrW, G_cntrH - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    addTextButton("144", 60, LIME, {G_cntrW - 300, G_cntrH + 50});
    addTextButton("31", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    addTextButton("2869", 60, VIOLET, {G_cntrW + 300, G_cntrH + 50});
    addTextButton("50", 100, PINK, {G_cntrW, G_cntrH + 50});
    addTextButton("518", 60, BLUE, {G_cntrW + 150, G_cntrH + 50});
}

void Level2::Update()
{
    // If the correct option is chosen, move on to Level 3.
    Level::Update();
    if (m_correctAnswer->isPressed()) {
        delete G_currentLevel;
        G_currentLevel = new Level3();
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete G_currentLevel;
                G_currentLevel = new LevelLose();
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
    addSimpleLabel("Level 3", 80, ORANGE, {G_cntrW, G_cntrH - 250}, 0);

    addSimpleLabel("What is the tallest number?", 40, RAYWHITE, {G_cntrW, G_cntrH - 150}, 0)
    ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_correctAnswer = addTextButton("144", 60, LIME, {G_cntrW - 300, G_cntrH + 50});
    addTextButton("31", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    addTextButton("2869", 60, VIOLET, {G_cntrW + 300, G_cntrH + 50});
    addTextButton("50", 100, PINK, {G_cntrW, G_cntrH + 50});
    addTextButton("518", 60, BLUE, {G_cntrW + 150, G_cntrH + 50}); 
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
        delete G_currentLevel;
        G_currentLevel = new Level4();
    }
    else {
        // If any button is pressed after it's determined the correct answer WASN'T pressed,
        // the player must have pressed the wrong button.
        for (Button* button : getButtons()) {
            if (button->isPressed()) {
                delete G_currentLevel;
                G_currentLevel = new LevelLose();
            }
        }
    } 
}

// ------------------------------------------------------------------------------------------ //
//                                          Level 4.                                          //
// ------------------------------------------------------------------------------------------ //
Level4::Level4()
{
    addSimpleLabel("Level 4", 80, ORANGE, {G_cntrW, G_cntrH - 250}, 0);

    addSimpleLabel("How much time do you want for Level 5?", 40, RAYWHITE, {G_cntrW, G_cntrH - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    addTextButton("2 seconds", 60, LIME, {G_cntrW, G_cntrH - 50});
    addTextButton("5 seconds", 60, VIOLET, {G_cntrW, G_cntrH + 50});
    addTextButton("10 seconds", 60, BLUE, {G_cntrW, G_cntrH + 150});
}

void Level4::Update()
{
    // If the correct option is chosen, move on to Level 5.
    Level::Update();
    
    // Find the button that was pressed, and set the next level's duration to that button's label.
    for (Button* button : getButtons()) {
        if (button->isPressed()) {
            // Save the chosen button's text to a string, then remove the " seconds" substring.
            string chosenTime = button->getLabel()->getText();
            chosenTime.erase(chosenTime.find(" seconds"), chosenTime.length());

            delete G_currentLevel;
            G_currentLevel = new Level5(chosenTime); 
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
    addSimpleLabel("Level  ", 80, ORANGE, {G_cntrW - 4, G_cntrH - 250}, 0);

    addTextButton("5", 80, ORANGE, {G_cntrW + 122, G_cntrH - 250});

    addSimpleLabel("Don't touch any numbers for", 40, RAYWHITE, {G_cntrW, G_cntrH - 150}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_timer = addTextButton(m_duration, 80, RED, {G_cntrW, G_cntrH - 65});

    addSimpleLabel("more seconds", 40, RAYWHITE, {G_cntrW, G_cntrH}, 0)
        ->setRotation(0.0f, 4.0f, 1.5f);

    // All obstacles.
    string longNumOne = "762967340328811348866734234450240332396217777462684390";
    string longNumTwo = "239427620310921174648449330989407894927458570770003111";
    string longNumThree = "230459256723665565627118580006023666643111673444567710";

    addTextButton("68", 120, RED, {G_cntrW - 270, G_cntrH - 500})->setSpeed({0, 12});
    addTextButton(longNumOne, 160, RED, {G_cntrW - 3050, G_cntrH + 250})->setSpeed({3, -1}); 
    addTextButton(longNumTwo, 160, RED, {G_cntrW + 3050, G_cntrH - 230})->setSpeed({-3, 1}); 
    addTextButton("8043001", 120, RED, {G_cntrW - 200, G_cntrH + 1200})->setSpeed({0, -5}); 
    addTextButton("3", 120, RED, {G_cntrW + 600, G_cntrH})->setSpeed({-1, 0});
    addTextButton("762", 160, RED, {G_cntrW - 1300, G_cntrH})->setSpeed({2, 0}); 
    addTextButton("12", 120, RED, {G_cntrW + 1800, G_cntrH - 600})->setSpeed({-8, 4});
    addTextButton("5000006", 120, RED, {G_cntrW + 200, G_cntrH - 3000})->setSpeed({0, 7}); 
    addTextButton("3078", 80, RED, {G_cntrW - 250, G_cntrH - 3100})->setSpeed({0, 7}); 
    addTextButton(longNumThree, 150, RED, {G_cntrW + 4550, G_cntrH - 150})->setSpeed({-4, 0}); 
    addTextButton("7877878447232634", 150, RED, {G_cntrW, G_cntrH + 800})->setSpeed({0, -1}); 
    addTextButton("64", 120, RED, {G_cntrW + 3000, G_cntrH + 700})->setSpeed({-5, -1});
}

void Level5::Update()
{
    GameLevel::Update();

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
            m_timer->getLabel()->setText(m_duration);
        }
        // If there is no time left...
        else { 
            delete G_currentLevel;
            G_currentLevel = new LevelTitle();
        } 
    } 
    
    // The lose condition can be this simple because all buttons on level 5 will be numbers.
    for (Button* button : getButtons()) {
        if (button->isHovered()) {
            delete G_currentLevel;
            G_currentLevel = new LevelLose();
        }
    }
}
