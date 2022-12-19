#include "LedMatrix.hpp"
#include <cstring>
#include "TM1640.hpp"

LedMatrix::LedMatrix(TM1640& ledDriver) :
    LedDriver_{ ledDriver }
{
}

void LedMatrix::begin()
{
    memset(Buffer_, 0, sizeof(Buffer_));

    for (uint8_t y = 0; y < HEIGHT; ++y)
    {
        LedDriver_.SetGrid(y, 0);
    }
}

int LedMatrix::GetPixel(int x, int y) const
{
    if (x < 0 || WIDTH <= x) return 0;
    if (y < 0 || HEIGHT <= y) return 0;

    int color = 0;
    for (int bit = 0; bit < COLOR_BITS; ++bit)
    {
        if (Buffer_[bit][y] & 1 << x) color |= 1 << bit;
    }

    return color;
}

void LedMatrix::SetPixel(int x, int y, int color)
{
    if (x < 0 || WIDTH <= x) return;
    if (y < 0 || HEIGHT <= y) return;

    for (int bit = 0; bit < COLOR_BITS; ++bit)
    {
        if (color & 1 << bit)
        {
            Buffer_[bit][y] |= 1 << x;
        }
        else
        {
            Buffer_[bit][y] &= ~(1 << x);
        }
    }

    for (int bit = 0; bit < COLOR_BITS; ++bit)
    {
        LedDriver_.SetGrid(8 * bit + y, Buffer_[bit][y]);
    }
}
