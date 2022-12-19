#pragma once

#include <cstdint>

class TM1640;

class LedMatrix
{
private:
    static constexpr int WIDTH = 8;
    static constexpr int HEIGHT = 8;
    static constexpr int COLOR_BITS = 2;

private:
    TM1640& LedDriver_;
    uint8_t Buffer_[COLOR_BITS][HEIGHT];

public:
    int Width() const
    {
        return WIDTH;
    }

    int Height() const
    {
        return HEIGHT;
    }

public:
    LedMatrix(TM1640& ledDriver);
    void begin();
    int GetPixel(int x, int y) const;
    void SetPixel(int x, int y, int color);

};
