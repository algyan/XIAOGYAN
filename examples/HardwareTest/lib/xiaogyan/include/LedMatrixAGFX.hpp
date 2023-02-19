/*
 * LedMatrixAGFX.hpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

#pragma once

#include <cstdint>
#include <Adafruit_GFX.h>

class LedMatrix;

class LedMatrixAGFX : public Adafruit_GFX
{
private:
    LedMatrix& ledMatrix_;

public:
    explicit LedMatrixAGFX(LedMatrix& ledMatrix);
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    
    void setBrightness(int brightness);

};
