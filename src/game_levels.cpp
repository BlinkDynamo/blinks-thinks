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
//                                GameLevel class definition.                                 //
// ------------------------------------------------------------------------------------------ //
GameLevel::GameLevel()
{

}

// Make a clickable UI button with dynamic label and background color at a fixed location.
Button* GameLevel::makeUiButton(string text)
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
Button* GameLevel::makeTextButton(string text, int fontSize, Color textColor, Vector2 position)
{
    constexpr int layer = 0;

    Label* const label = new Label(text, fontSize, textColor, G_shadowColor, position, layer);

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
    m_playButton(nullptr)
{
    // Non-referenced objects.
    (void)addEntity(new Label(
        "Blink's Thinks", 100, RAYWHITE, G_shadowColor, {G_cntrW, G_cntrH - 100}, 0)
    )
    ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_playButton = makeUiButton("Play");
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
    (void)addEntity(new Label(
        "Game over!", 100, RED, G_shadowColor, {G_cntrW, G_cntrH - 100}, 0)
    )
    ->setRotation(0.0f, 5.0f, 2.5f);

    // Class-referenced objects. 
    m_restartButton = makeUiButton("Restart");
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
    (void)addEntity(new Label(
        "Level 1", 80, ORANGE, G_shadowColor, {G_cntrW, G_cntrH - 250}, 0)
    );
    
    (void)addEntity(new Label(
        "What is the largest number?", 40, RAYWHITE, G_shadowColor, {G_cntrW,
        G_cntrH - 150}, 0)
    )
    ->setRotation(0.0f, 4.0f, 1.5f);

    (void)makeTextButton("144", 60, LIME, {G_cntrW - 300, G_cntrH + 50});
    (void)makeTextButton("31", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    (void)makeTextButton("50", 100, PINK, {G_cntrW, G_cntrH + 50});
    (void)makeTextButton("518", 60, BLUE, {G_cntrW + 150, G_cntrH + 50});
    m_correctAnswer = makeTextButton("2869", 60, VIOLET, {G_cntrW + 300, G_cntrH + 50}); 
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
    (void)addEntity(new Label(
        "Level  ", 80, ORANGE, G_shadowColor, {G_cntrW - 4, G_cntrH - 250}, 0)
    );

    m_correctAnswer = makeTextButton("2", 80, ORANGE, {G_cntrW + 122, G_cntrH - 250});

    (void)addEntity(new Label(
        "What is the smallest number?", 40, RAYWHITE, G_shadowColor, {G_cntrW,
        G_cntrH - 150}, 0)
    )
    ->setRotation(0.0f, 4.0f, 1.5f);
    
    (void)makeTextButton("144", 60, LIME, {G_cntrW - 300, G_cntrH + 50});
    (void)makeTextButton("31", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    (void)makeTextButton("2869", 60, VIOLET, {G_cntrW + 300, G_cntrH + 50});
    (void)makeTextButton("50", 100, PINK, {G_cntrW, G_cntrH + 50});
    (void)makeTextButton("518", 60, BLUE, {G_cntrW + 150, G_cntrH + 50});
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
    (void)addEntity(new Label(
        "Level 3", 80, ORANGE, G_shadowColor, {G_cntrW, G_cntrH - 250}, 0)
    );

    (void)addEntity(new Label(
        "What is the tallest number?", 40, RAYWHITE, G_shadowColor, {G_cntrW,
        G_cntrH - 150}, 0)
    )
    ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_correctAnswer = makeTextButton("144", 60, LIME, {G_cntrW - 300, G_cntrH + 50});
    (void)makeTextButton("31", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    (void)makeTextButton("2869", 60, VIOLET, {G_cntrW + 300, G_cntrH + 50});
    (void)makeTextButton("50", 100, PINK, {G_cntrW, G_cntrH + 50});
    (void)makeTextButton("518", 60, BLUE, {G_cntrW + 150, G_cntrH + 50}); 
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
    (void)addEntity(new Label(
        "Level 4", 80, ORANGE, G_shadowColor, {G_cntrW, G_cntrH - 250}, 0)
    );

    (void)addEntity(new Label(
        "How much time do you want for Level 5?", 40, RAYWHITE, G_shadowColor,
        {G_cntrW, G_cntrH - 150}, 0)
    )
    ->setRotation(0.0f, 4.0f, 1.5f);
    
    (void)makeTextButton("10", 80, LIME, {G_cntrW - 300, G_cntrH + 50});
    (void)makeTextButton("20", 80, GOLD, {G_cntrW - 150, G_cntrH + 50});
    (void)makeTextButton("30", 80, VIOLET, {G_cntrW + 300, G_cntrH + 50});
    (void)makeTextButton("60", 80, PINK, {G_cntrW, G_cntrH + 50});
    (void)makeTextButton("120", 80, BLUE, {G_cntrW + 150, G_cntrH + 50});
}

void Level4::Update()
{
    // If the correct option is chosen, move on to Level 3.
    Level::Update();
    
    // Find the button that was pressed, and set the next level's duration to that button's label.
    for (Button* button : getButtons()) {
        if (button->isPressed()) {
            delete G_currentLevel;
            G_currentLevel = new Level5(button->getLabel()->getText()); 
        }
    }
}

Level5::Level5(string duration)
    :
    m_timer(nullptr),
    m_framesCounter(0),
    m_duration(duration)
{
    (void)addEntity(new Label(
        "Level 5", 80, ORANGE, G_shadowColor, {G_cntrW, G_cntrH - 250}, 0)
    );

    (void)addEntity(new Label(
        "Survive!", 40, RAYWHITE, G_shadowColor, {G_cntrW, G_cntrH - 150}, 0)
    )
    ->setRotation(0.0f, 4.0f, 1.5f);
    
    m_timer = addEntity(new Label(
        m_duration, 80, LIME, G_shadowColor, {G_cntrW, G_cntrH - 50}, 0)
    );
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
            // Reset the frames counter and decrement the time by 1. If the time ('i') just now reached 0,
            // set the level overlay to green.
            m_framesCounter = 0;
            i--;
            
            // Turn 'i' back into a string, and set the text of m_timer to this.
            std::ostringstream oss;
            oss << i;
            m_duration = oss.str();
            m_timer->setText(m_duration);
        }
        // If there is no time left...
        else { 
            delete G_currentLevel;
            G_currentLevel = new LevelTitle();
        }
    } 
}
