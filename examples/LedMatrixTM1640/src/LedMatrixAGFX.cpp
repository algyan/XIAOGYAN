#include "LedMatrixAGFX.hpp"
#include "LedMatrix.hpp"

LedMatrixAGFX::LedMatrixAGFX(LedMatrix& ledMatrix) :
    Adafruit_GFX{ static_cast<int16_t>(ledMatrix.Width()), static_cast<int16_t>(ledMatrix.Height()) },
    LedMatrix_{ ledMatrix }
{
}

void LedMatrixAGFX::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    LedMatrix_.SetPixel(x, y, color);
}
