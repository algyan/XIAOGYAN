#pragma once

#include <Adafruit_GFX.h>

class LedMatrix;

class LedMatrixAGFX : public Adafruit_GFX
{
private:
    LedMatrix& LedMatrix_;

public:
    LedMatrixAGFX(LedMatrix& ledMatrix);
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;

};
