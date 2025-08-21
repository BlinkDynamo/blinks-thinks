/***********************************************************************************************
*
*   game_levels.hpp - The implementation of the level class. All levels used in the game are
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

using engine::game;

// Standard library.
#include <iterator>
#include <algorithm>

using std::to_string;

// ------------------------------------------------------------------------------------------ //
//                                     Raylib animation.                                      //
// ------------------------------------------------------------------------------------------ //
intro_raylib::intro_raylib()
    :
    m_animation(add_entity(new anim_raylib()))
{
    m_game.set_current_music_by_name("title_theme"); 
    PlayMusicStream(*m_game.get_current_music());
}

void intro_raylib::update() {
    level::update(); 

    if (m_animation->isFinished()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new intro_self_credit());
        return;
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_title());
        return;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                   Self credit animation.                                   //
// ------------------------------------------------------------------------------------------ //
intro_self_credit::intro_self_credit()
    :
    m_animation(add_entity(new anim_self_credit()))
{}

void intro_self_credit::update()
{
    level::update();

    if (m_animation->isFinished() || IsKeyPressed(KEY_ENTER)) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_title());
        return;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                       Title screen.                                        //
// ------------------------------------------------------------------------------------------ //
level_title::level_title()
    :
    m_game_title_text{
        .text_obj = add_simple_text("Blink's Thinks", 100, m_game_title_text.text_color, {m_game.get_cw(), m_game.get_ch() - 100}, 0)
    },
    m_play_button(add_ui_button("Play"))
{
    this->m_game_title_text.text_obj->add_anim_rotate(0.0f, 5.0f, 2.5f);
}

void level_title::update()
{
    level::update(); 
    
    if (m_play_button->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new intro_section_one());
        return;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                        Lose screen.                                        //
// ------------------------------------------------------------------------------------------ //
level_lose::level_lose()
    :
    m_restart_button(add_ui_button("Restart"))
{
    add_simple_text("game over!", 100, RED, {m_game.get_cw(), m_game.get_ch() - 100}, 0)
        ->add_anim_rotate(0.0f, 5.0f, 2.5f);
}

void level_lose::update()
{
    level::update();

    // Pitch down the current music track.
    constexpr float epsilon = 0.0001f;
    if (m_game.get_current_music_pitch() > 0.8f + epsilon) {
        SetMusicPitch(*m_game.get_current_music(), m_game.get_current_music_pitch());
        m_game.set_current_music_pitch(m_game.get_current_music_pitch() - 0.01);
    }

    if (m_restart_button->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new intro_section_one());
        return;
    }
}

// ------------------------------------------------------------------------------------------ //
//                               Section Introduction: Numbers.                               //
// ------------------------------------------------------------------------------------------ //
intro_section_one::intro_section_one()
    : m_frames_counter(0)
{
    add_simple_text("Levels 1-10: Numbers", 60, GREEN, {m_game.get_cw(), m_game.get_ch() - 100}, 0);

    // Set the music track. 
    m_game.set_current_music_by_name("no_stopping_now");
    PlayMusicStream(*m_game.get_current_music());
}

void intro_section_one::update()
{
    level::update();   
    ++m_frames_counter;
    if (m_frames_counter == 3 * m_game.get_frame_rate()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_one());
        return;
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          level 1.                                          //
// ------------------------------------------------------------------------------------------ //
level_one::level_one() 
{
    constexpr int level_num = 1;
    constexpr int choice_count = 5;
    constexpr int min_choice = 1;
    constexpr int max_choice = 25;
    constexpr int font_size = 80;
    constexpr float button_x_offset_per_iter = 150;

    float button_x = m_game.get_cw() - 300;

    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);
    m_correct_button = add_text_button(to_string(level_num), 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250});
    
    add_simple_text("What is the largest number?", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);
   
    vector<int> choices; 
    choices.push_back(level_num);    
    int largest_choice = level_num;

    for (int i = 0; i < choice_count; i++) {
        // Get a unique choice value and store it in 'choices' for future checking.
        int choice = m_game.random_int_in_range(min_choice, max_choice);

        while (find(choices.begin(), choices.end(), choice) != choices.end()) {
            choice = m_game.random_int_in_range(min_choice, max_choice);
        }
        choices.push_back(choice);
        

        // The buttons' Y value will flip-flop between iterations of being positioned higher and
        // lower inside the level.
        float button_y = (i % 2) ? m_game.get_ch() - 25 : m_game.get_ch() + 175;

        button* btn = add_text_button(to_string(choice), font_size, m_game.random_bright_color(),
                                       {button_x, button_y});
        button_x += button_x_offset_per_iter;

        if (choice > largest_choice) {
            largest_choice = choice;
            m_correct_button = btn;
        }
    } 
}

void level_one::update()
{
    level::update();
    
    // Pitch back up the current music track if it's below 1.0. Since the player will always
    // restart at level 1, this only needs to be handled here.
    constexpr float epsilon = 0.0001f; 
    if (m_game.get_current_music_pitch() < 1.0 - epsilon) {
        SetMusicPitch(*m_game.get_current_music(), m_game.get_current_music_pitch());
        m_game.set_current_music_pitch(m_game.get_current_music_pitch() + 0.02);
    }

    if (m_correct_button->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_two());
        return;
    }
    else {
        for (button* btn : get_buttons()) {
            if (btn->is_pressed()) {
                delete m_game.get_current_level();
                m_game.set_current_level(new level_lose());
                return;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          level 2.                                          //
// ------------------------------------------------------------------------------------------ //
level_two::level_two()
{
    constexpr int level_num = 2;
    constexpr int choice_count = 5;
    constexpr int min_choice = 1;
    constexpr int max_choice = 25;
    constexpr int font_size = 80;
    constexpr float button_x_offset_per_iter = 150;

    float button_x = m_game.get_cw() - 300;

    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);

    add_simple_text("What is the smallest number?", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);
    
    vector<int> choices;

    m_correct_button = add_text_button(to_string(level_num), 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250});
    choices.push_back(level_num);
    int smallest_choice = level_num;

    for (int i = 0; i < choice_count; i++) {
        // Get a unique choice value and store it in 'choices' for future checking.
        int choice = m_game.random_int_in_range(min_choice, max_choice);

        while (find(choices.begin(), choices.end(), choice) != choices.end()) {
            choice = m_game.random_int_in_range(min_choice, max_choice);
        }
        choices.push_back(choice);

        // The buttons' Y value will flip-flop between iterations of being positioned higher and
        // lower inside the level.
        float button_y = (i % 2) ? m_game.get_ch() - 25 : m_game.get_ch() + 175;

        button* btn = add_text_button(to_string(choice), font_size, m_game.random_bright_color(),
                                       {button_x, button_y});
        button_x += button_x_offset_per_iter;

        if (choice < smallest_choice) {
            smallest_choice = choice;
            m_correct_button = btn;
        }
    }
}

void level_two::update()
{
    level::update();

    if (m_correct_button->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_three());
        return;
    }
    else {
        for (button* btn : get_buttons()) {
            if (btn->is_pressed()) {
                delete m_game.get_current_level();
                m_game.set_current_level(new level_lose());
                return;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          level 3.                                          //
// ------------------------------------------------------------------------------------------ //
level_three::level_three()
    :
    m_correct_button{
        .button_ptr = nullptr,
        .current_scale = 1.0
    }
{
    constexpr int level_num = 3;
    constexpr int choice_count = 5;
    constexpr int min_choice = 1;
    constexpr int max_choice = 25;
    constexpr int font_size = 80;
    constexpr float button_x_offset_per_iter = 150;

    float button_x = m_game.get_cw() - 300;

    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw(), m_game.get_ch() - 250}, 0);

    add_simple_text("What is the tallest number?", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
    ->add_anim_rotate(0.0f, 4.0f, 1.5f);
     
    m_answer_choices[level_num] = add_text_button(
        to_string(level_num), 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250}
    );

    for (int i = 0; i < choice_count; i++) {
        // Get a unique choice value and store it in 'choices' for future checking.
        int choice = m_game.random_int_in_range(min_choice, max_choice);

        while (m_answer_choices.find(choice) != m_answer_choices.end()) {
            choice = m_game.random_int_in_range(min_choice, max_choice);
        }

        // The buttons' Y value will flip-flop between iterations of being positioned higher and
        // lower inside the level.
        float button_y = (i % 2) ? m_game.get_ch() - 25 : m_game.get_ch() + 175;

        m_answer_choices[choice] = add_text_button(
                to_string(choice), font_size, m_game.random_bright_color(), {button_x, button_y}
        );

        button_x += button_x_offset_per_iter; 
    }

    // Choose a random member of 'm_answer_choices' to be the correct answer. 
    const int random_index = m_game.random_int_in_range(0, static_cast<int>(m_answer_choices.size()) - 1);
    unordered_map<int, button*>::iterator it = m_answer_choices.begin();
    std::advance(it, random_index);
    m_correct_button.button_ptr = it->second;
}

void level_three::update()
{
    // If the correct option is hovered, make it grow in scale. Otherwise, make it shrink until
    // it becomes it's normal scale again. 
    if (m_correct_button.button_ptr->is_hovered()) {
        if (m_correct_button.current_scale < m_correct_button.max_scale) {
            m_correct_button.current_scale += m_correct_button.scale_up_incr;
            m_correct_button.button_ptr->set_scale(m_correct_button.current_scale);
        }
    }
    else if (m_correct_button.current_scale > m_correct_button.min_scale) {
            m_correct_button.current_scale -= m_correct_button.scale_down_incr;
            m_correct_button.button_ptr->set_scale(m_correct_button.current_scale);
    }

    level::update();
    if (m_correct_button.button_ptr->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_four());
        return;
    }
    else {
        for (button* btn : get_buttons()) {
            if (btn->is_pressed()) {
                delete m_game.get_current_level();
                m_game.set_current_level(new level_lose());
                return;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------ //
//                                          level 4.                                          //
// ------------------------------------------------------------------------------------------ //
level_four::level_four()
{
    add_simple_text("level 4", 80, ORANGE, {m_game.get_cw(), m_game.get_ch() - 250}, 0);

    add_simple_text("How much time do you want for level 5?", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);

    add_text_button("2 seconds", 60, m_game.random_bright_color(), {m_game.get_cw(), m_game.get_ch() - 50});
    add_text_button("5 seconds", 60, m_game.random_bright_color(), {m_game.get_cw(), m_game.get_ch() + 50});
    add_text_button("10 seconds", 60, m_game.random_bright_color(), {m_game.get_cw(), m_game.get_ch() + 150});
}

void level_four::update()
{
    level::update();

    for (button* btn : get_buttons()) {
        if (btn->is_pressed()) {
            string chosen_time = btn->get_text_obj()->get_text_str();
            chosen_time.erase(chosen_time.find(" seconds"), chosen_time.length());
            delete m_game.get_current_level();
            m_game.set_current_level(new level_five(chosen_time));
            return;
        }
    }
}

level_five::level_five(string duration)
    :
    m_frames_counter(0),
    m_duration(duration),
    m_timer(add_text_button(m_duration, 80, RED, {m_game.get_cw(), m_game.get_ch() - 65}))
{
    // Main level_title, information, and countdown timer.
    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);

    add_text_button("5", 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250});

    add_simple_text("Don't touch any numbers for", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);

    add_simple_text("more seconds", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch()}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);

    // All obstacles.
    const string long_num_one = "762967340328811348866734234450240332396217777462684390";
    const string long_num_two = "239427620310921174648449330989407894927458570770003111";
    const string long_num_three = "230459256723665565627118580006023666643111673444567710";

    add_text_button("68", 120, RED, {m_game.get_cw() - 270, m_game.get_ch() - 500})->set_speed({0, 12});
    add_text_button(long_num_one, 160, RED, {m_game.get_cw() - 3050, m_game.get_ch() + 250})->set_speed({3, -1});
    add_text_button(long_num_two, 160, RED, {m_game.get_cw() + 3050, m_game.get_ch() - 230})->set_speed({-3, 1});
    add_text_button("8043001", 120, RED, {m_game.get_cw() - 200, m_game.get_ch() + 1200})->set_speed({0, -5});
    add_text_button("3", 120, RED, {m_game.get_cw() + 600, m_game.get_ch()})->set_speed({-1, 0});
    add_text_button("762", 160, RED, {m_game.get_cw() - 1300, m_game.get_ch()})->set_speed({2, 0});
    add_text_button("12", 120, RED, {m_game.get_cw() + 1800, m_game.get_ch() - 600})->set_speed({-8, 4});
    add_text_button("5000006", 120, RED, {m_game.get_cw() + 200, m_game.get_ch() - 3000})->set_speed({0, 7});
    add_text_button("3078", 80, RED, {m_game.get_cw() - 250, m_game.get_ch() - 3100})->set_speed({0, 7});
    add_text_button(long_num_three, 150, RED, {m_game.get_cw() + 4550, m_game.get_ch() - 150})->set_speed({-4, 0});
    add_text_button("7877878447232634", 150, RED, {m_game.get_cw(), m_game.get_ch() + 800})->set_speed({0, -1});
    add_text_button("64", 120, RED, {m_game.get_cw() + 3000, m_game.get_ch() + 700})->set_speed({-5, -1});
}

void level_five::update()
{
    level::update();

    // update the timer once per 60 frames.
    m_frames_counter++; 
    if (m_frames_counter == 60) { 
        int duration_as_int = TextToInteger(m_duration.c_str());
        if (duration_as_int > 0) {
            m_frames_counter = 0;
            --duration_as_int;
            
            m_duration = to_string(duration_as_int);
            m_timer->get_text_obj()->set_text_str(m_duration);
        }
        else {
            delete m_game.get_current_level();
            m_game.set_current_level(new level_six());
            return;
        }
    }

    // The level_lose condition can be this simple because all buttons on level 5 will be numbers.
    for (button* btn : get_buttons()) {
        if (btn->is_hovered()) {
            delete m_game.get_current_level();
            m_game.set_current_level(new level_lose());
            return;
        }
    }
}

level_six::level_six()
    :
    m_correct_button(add_text_button("3", 80, m_game.random_bright_color(), {m_game.get_cw() - 225, m_game.get_ch() + 175}))
{
    //
    // Main level_title and instructions.
    //
    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);
    add_text_button("6", 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250});

    add_simple_text("What is the first number of something delicious?", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);

    add_text_button("5", 80, m_game.random_bright_color(), {m_game.get_cw() - 275, m_game.get_ch()});
    add_text_button("7", 80, m_game.random_bright_color(), {m_game.get_cw() + 225, m_game.get_ch() + 175});
    add_text_button("9", 80, m_game.random_bright_color(), {m_game.get_cw() + 275, m_game.get_ch()});
}

void level_six::update()
{
    level::update(); 

    for (button* btn : get_buttons()) {
        if (btn->is_pressed()) {
            if (btn == m_correct_button) {
                delete m_game.get_current_level();
                m_game.set_current_level(new level_seven());
                return;
            }
            else {
                delete m_game.get_current_level();
                m_game.set_current_level(new level_lose());
                return;
            }
        }
    }
}

level_seven::level_seven()
:
    m_button_in_hand(nullptr),
    m_submit_box(add_entity(new label(BLACK, WHITE, {250, 150}, 6, {m_game.get_cw(), m_game.get_ch() - 25}, -10))),
    m_submit_button(add_ui_button("Submit")),
    m_correct_number("7")
{
    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);

    add_text_button("7", 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250});

    add_simple_text("Put the hungry number in the box", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);

    add_text_button("5", 80, m_game.random_bright_color(), {m_game.get_cw() - 275, m_game.get_ch()});
    add_text_button("6", 80, m_game.random_bright_color(), {m_game.get_cw() - 225, m_game.get_ch() + 175});
    add_text_button("8", 80, m_game.random_bright_color(), {m_game.get_cw() + 225, m_game.get_ch() + 175});
    add_text_button("10", 80, m_game.random_bright_color(), {m_game.get_cw() + 275, m_game.get_ch()});
}

void level_seven::update()
{
    level::update();

    // The number-dragging can be this simple because all buttons are numbers except the 'Submit' button.
    for (button* btn : get_buttons()) {
        if (btn->is_pressed() && btn != m_submit_button) {
            // point 'm_btnInHand' to the btn that was just pressed, setting it back to
            // 'nullptr' if the mouse is released.
            m_button_in_hand = btn;
        }
    }

    if (IsMouseButtonDown(0) && m_button_in_hand != nullptr) {
        m_button_in_hand->set_position(GetMousePosition());
    }
    else {
        m_button_in_hand = nullptr;
    }

    // On submission, add every button inside of the submission box to a vector, then organize
    // their text object's text strings in the same order that they exist spatially. Save this
    // created number to a string and check if it matches 'm_correct_number'.
    if (m_submit_button->is_pressed()) {
        vector<button*> numbers_in_box; // For buttons that are inside of the submission box.
        string final_submission; // The final submission to match against 'm_correct_number'.
        for (button* btn : get_buttons()) {
            if (CheckCollisionRecs(btn->get_rectangle(), m_submit_box->get_rectangle())) {
                vector<button*>::iterator it = numbers_in_box.begin();
                while (it != numbers_in_box.end() && (*it)->get_position().x <= btn->get_position().x) {
                    ++it;
                }
                numbers_in_box.insert(it, btn);
            }
        }
        for (button* btn : numbers_in_box) {
            final_submission += btn->get_text_obj()->get_text_str();
        }

        if (final_submission == m_correct_number) {
            delete m_game.get_current_level();
            m_game.set_current_level(new level_eight());
            return;
        }
        else {
            delete m_game.get_current_level();
            m_game.set_current_level(new level_lose());
            return;
        }
    }
}

level_eight::level_eight()
    :
    m_submit_button(add_ui_button("Next"))
{
    //
    // Main level_title and instructions.
    //
    add_simple_text("level 8", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);
}

void level_eight::update()
{
    level::update(); 

    if (m_submit_button->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_nine());
        return;
    }
}

level_nine::level_nine()
    :
    m_button_in_hand(nullptr),
    m_submit_box(add_entity(new label(BLACK, WHITE, {250, 150}, 9, {m_game.get_cw(), m_game.get_ch() - 25}, -10))),
    m_submit_button(add_ui_button("Submit"))
{
    //
    // Main level_title and instructions.
    //
    add_simple_text("level  ", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);

    add_simple_text("Fit the greatest number into the box", 40, RAYWHITE, {m_game.get_cw(), m_game.get_ch() - 150}, 0)
        ->add_anim_rotate(0.0f, 4.0f, 1.5f);

    //
    // button creation.
    //
    m_correct_button_layout.reserve(m_choice_count);

    button* number_in_level_title = add_text_button("9", 80, ORANGE, {m_game.get_cw() + 122, m_game.get_ch() - 250});
    this->m_correct_button_layout.push_back(number_in_level_title);

    while (m_correct_button_layout.size() < m_choice_count) {
        int choice_value = m_game.random_int_in_range(1, 9);
        Color color = m_game.random_bright_color();
        Vector2 pos = {m_game.get_cw(), m_game.get_ch()};
        button* newest_button = add_text_button(to_string(choice_value), 80, color, pos); 
        m_correct_button_layout.push_back(newest_button);
    }

    sort(m_correct_button_layout.begin(), m_correct_button_layout.end(),
        [](button* a, button* b) {
            return a->get_text_obj()->get_text_str() > b->get_text_obj()->get_text_str();
        }
    );
}

void level_nine::update()
{
    level::update();

    // The number-dragging can be this simple because all buttons are numbers except the 'Submit' button.
    for (button* btn : get_buttons()) {
        if (btn->is_pressed() && btn != m_submit_button) { 
            m_button_in_hand = btn; 
        }
    }

    if (IsMouseButtonDown(0) && m_button_in_hand != nullptr) {
        m_button_in_hand->set_position(GetMousePosition());
    }
    else {
        m_button_in_hand = nullptr;
    }

    //
    // On submission, add every button inside of the submission box to a vector, then organize
    // their text object's text strings in the same order that they exist spatially. Save this
    // created number to a string and check if it matches 'm_correct_number'.
    //
    if (m_submit_button->is_pressed()) {

        vector<button*> numbers_in_box; // For buttons that are inside of the submission box.
        numbers_in_box.reserve(m_choice_count);

        for (button* btn : get_buttons()) {
            if (CheckCollisionRecs(btn->get_rectangle(), m_submit_box->get_rectangle())) {
                vector<button*>::iterator it = numbers_in_box.begin();
                while (it != numbers_in_box.end() && (*it)->get_position().x <= btn->get_position().x) {
                    ++it;
                }
                numbers_in_box.insert(it, btn);
            }
        }

        // Assume true and override if proven false. 
        bool answer_was_chosen = true;
        vector<button*>::iterator choice_it = numbers_in_box.begin();
        vector<button*>::iterator answer_it = m_correct_button_layout.begin();
        for (; choice_it != numbers_in_box.end() && answer_it != m_correct_button_layout.end(); ++choice_it, ++answer_it) {
            if ((*choice_it)->get_text_obj()->get_text_str() != (*answer_it)->get_text_obj()->get_text_str()) {
                answer_was_chosen = false;
            }
        }

        if (answer_was_chosen) {
            delete m_game.get_current_level();
            m_game.set_current_level(new level_ten());
            return;
        }
        else {
            delete m_game.get_current_level();
            m_game.set_current_level(new level_lose());
            return;
        }
    }
}

level_ten::level_ten()
    :
    m_submit_button(add_ui_button("Next"))
{
    //
    // Main level_title and instructions.
    //
    add_simple_text("level 10", 80, ORANGE, {m_game.get_cw() - 4, m_game.get_ch() - 250}, 0);
}

void level_ten::update()
{
    level::update();

    if (m_submit_button->is_pressed()) {
        delete m_game.get_current_level();
        m_game.set_current_level(new level_title());
        return;
    }
}
