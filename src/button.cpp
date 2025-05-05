#include "blinks-thinks/button.hpp"

Button::Button(const char * text, Vector2 position, Vector2 size, Color bgColor, Color textColor)
{
    this->text = text;
    /* 'position' places the button based on it's center position. */
    this->position = {position.x -= size.x / 2.0f, position.y -= size.y / 2.0f };
    this->size = size;
    this->bgColor = bgColor;
    this->textColor = textColor;
}
    
void Button::Draw()
{
    DrawRectangleV(position, size, bgColor);

    int fontSize = 20;
    /* Center the text inside the button. */
    int textWidth = MeasureText(text, fontSize);
    int textX = position.x + (size.x - textWidth) / 2;
    int textY = position.y + (size.y - fontSize) / 2;

    DrawText(text, textX, textY, fontSize, textColor);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed)
{
    Rectangle rect = { position.x, position.y, size.x, size.y };
    return CheckCollisionPointRec(mousePos, rect) && mousePressed;
}
