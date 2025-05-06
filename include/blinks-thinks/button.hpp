#pragma once

#include <raylib/raylib.h>
#include <string>

class Button {
    public:
        Button(const char * text, int fontSize, Vector2 position, Vector2 size, Color bgColor,
               Color textColor);
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);

    private:
        const char *text;
        int fontSize;
        Vector2 position;
        Vector2 size;
        Color bgColor;
        Color textColor;
};
