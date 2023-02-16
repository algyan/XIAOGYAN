#pragma once

#include <cstdint>
#include <ArduinoEigen.h>

class TM1640;

class LedMatrix
{
public:
    enum class ScreenRotation
    {
        Degree0,
        Degree90,
        Degree180,
        Degree270,
    };

private:
    static constexpr int WIDTH = 8;
    static constexpr int HEIGHT = 8;
    static constexpr int COLOR_BITS = 2;

private:
    TM1640& LedDriver_;
    Eigen::Matrix<int, 3, 3> ScreenAffineTransformation_;
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
    explicit LedMatrix(TM1640& ledDriver);
    void begin();
    void begin(bool flip, ScreenRotation screenRotation);
    int GetPixel(int x, int y) const;
    void SetPixel(int x, int y, int color);

};
