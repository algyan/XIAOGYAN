/*
 * LedMatrixAGFX.cpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include "LedMatrixAGFX.hpp"
#include "LedMatrix.hpp"
#include "TM1640.hpp"

////////////////////////////////////////////////////////////////////////////////
// LedMatrixAGFX

LedMatrixAGFX::LedMatrixAGFX(LedMatrix& ledMatrix) :
    Adafruit_GFX{ static_cast<int16_t>(ledMatrix.width()), static_cast<int16_t>(ledMatrix.height()) },
    ledMatrix_{ ledMatrix }
{
}

void LedMatrixAGFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    ledMatrix_.setPixel(x, y, color);
}

void LedMatrixAGFX::setBrightness(int brightness)
{
    ledMatrix_.getLedDriver().setBrightness(brightness);
}

////////////////////////////////////////////////////////////////////////////////
