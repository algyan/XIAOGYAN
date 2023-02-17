/*
 * LedMatrix.cpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include "LedMatrix.hpp"
#include <cstring>
#include "TM1640.hpp"

////////////////////////////////////////////////////////////////////////////////
// LedMatrix

LedMatrix::LedMatrix(TM1640& ledDriver) :
    ledDriver_{ ledDriver }
{
}

void LedMatrix::begin()
{
    screenAffineTransformation_ << 1, 0, 0,
                                   0, 1, 0,
                                   0, 0, 1;

    memset(buffer_, 0, sizeof(buffer_));
    for (uint8_t y = 0; y < HEIGHT; ++y) ledDriver_.setGrid(y, 0);
}

void LedMatrix::begin(bool flip, ScreenRotation screenRotation)
{
    screenAffineTransformation_ << 1, 0, 0,
                                   0, 1, 0,
                                   0, 0, 1;

    if (flip)
    {
        Eigen::Matrix<int, 3, 3> affine;
        affine << 1,  0,          0,
                  0, -1, HEIGHT - 1,
                  0,  0,          1;

        screenAffineTransformation_ = affine * screenAffineTransformation_;
    }

    int rotate90Number;
    switch (screenRotation)
    {
    case ScreenRotation::Degree0:
        rotate90Number = 0;
        break;
    case ScreenRotation::Degree90:
        rotate90Number = 1;
        break;
    case ScreenRotation::Degree180:
        rotate90Number = 2;
        break;
    case ScreenRotation::Degree270:
        rotate90Number = 3;
        break;
    default:
        abort();
    }
    if (rotate90Number >= 1)
    {
        Eigen::Matrix<int, 3, 3> affine;
        affine << 0, -1, WIDTH - 1, // For now, I can only specify the WIDTH.
                  1,  0,         0,
                  0,  0,         1;

        for (int i = 0; i < rotate90Number; ++i)
        {
            screenAffineTransformation_ = affine * screenAffineTransformation_;
        }
    }

    memset(buffer_, 0, sizeof(buffer_));
    for (uint8_t y = 0; y < HEIGHT; ++y) ledDriver_.setGrid(y, 0);
}


int LedMatrix::getPixel(int x, int y) const
{
    if (x < 0 || WIDTH <= x) return 0;
    if (y < 0 || HEIGHT <= y) return 0;

    Eigen::Matrix<int, 3, 1> pixel;
    pixel << x, y, 1;
    pixel = screenAffineTransformation_ * pixel;
    x = pixel(0, 0);
    y = pixel(1, 0);

    int color = 0;
    for (int bit = 0; bit < COLOR_BITS; ++bit)
    {
        if (buffer_[bit][y] & 1 << x) color |= 1 << bit;
    }

    return color;
}

void LedMatrix::setPixel(int x, int y, int color)
{
    if (x < 0 || WIDTH <= x) return;
    if (y < 0 || HEIGHT <= y) return;

    Eigen::Matrix<int, 3, 1> pixel;
    pixel << x, y, 1;
    pixel = screenAffineTransformation_ * pixel;
    x = pixel(0, 0);
    y = pixel(1, 0);

    for (int bit = 0; bit < COLOR_BITS; ++bit)
    {
        if (color & 1 << bit)
        {
            buffer_[bit][y] |= 1 << x;
        }
        else
        {
            buffer_[bit][y] &= ~(1 << x);
        }
    }

    for (int bit = 0; bit < COLOR_BITS; ++bit)
    {
        ledDriver_.setGrid(8 * bit + y, buffer_[bit][y]);
    }
}

////////////////////////////////////////////////////////////////////////////////
