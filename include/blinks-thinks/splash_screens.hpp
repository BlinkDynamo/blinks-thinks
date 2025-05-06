#pragma once

#include <raylib/raylib.h>

class RaylibSplash
{
    public:
        RaylibSplash(int screenWidth,int screenHeight);
        void Draw();

    private:
        int screenWidth;
        int screenHeight;
};

class BlinkSoftwareSplash
{
    public:
        BlinkSoftwareSplash(int screenWidth,int screenHeight);
        void Draw();

    private:
        int screenWidth;
        int screenHeight;
};
