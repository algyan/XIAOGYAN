#include "TM1640.hpp"
#include <Arduino.h>

void TM1640::Init()
{
    pinMode(DinPin_, OUTPUT);
    pinMode(SclkPin_, OUTPUT);
    digitalWrite(DinPin_, HIGH);
    digitalWrite(SclkPin_, HIGH);
    delayMicroseconds(1);
}

void TM1640::Start()
{
    digitalWrite(DinPin_, LOW);
    delayMicroseconds(1);
}

void TM1640::Write(uint8_t data)
{
    for (int i = 0; i < 8; ++i)
    {
        digitalWrite(SclkPin_, LOW);
        digitalWrite(DinPin_, data & 0x01 ? HIGH : LOW);
        digitalWrite(SclkPin_, HIGH);
        delayMicroseconds(1);

        data >>= 1;
    }
}

void TM1640::End()
{
    digitalWrite(SclkPin_, LOW);
    digitalWrite(DinPin_, LOW);
    digitalWrite(SclkPin_, HIGH);
    delayMicroseconds(1);
    digitalWrite(DinPin_, HIGH);
    delayMicroseconds(1);
}

TM1640::TM1640(int dinPin, int sclkPin) :
    DinPin_{ dinPin },
    SclkPin_{ sclkPin },
    GridMap_{ nullptr },
    SegMap_{ nullptr }
{
}

TM1640::TM1640(int dinPin, int sclkPin, const uint8_t gridMap[16], const uint8_t segMap[8]) :
    DinPin_{ dinPin },
    SclkPin_{ sclkPin },
    GridMap_{ gridMap },
    SegMap_{ segMap }
{
}

void TM1640::begin()
{
    Init();

    Start();
    Write(0b01000000);  // Data command setting : Address auto + 1
    End();
}

void TM1640::SetBrightness(int brightness)
{
    if (brightness < 0) brightness = 0;
    if (brightness > 8) brightness = 8;

    Start();
    if (brightness == 0)
    {
        Write(0b10000000);                  // Display control command setting : Display off
    }
    else
    {
        Write(0b10001000 | brightness - 1); // Display control command setting : Set pulse width to 1/16-14/16
    }
    End();
}

void TM1640::SetGrid(uint8_t grid, uint8_t segs)
{
    if (grid >= 16) return;

    if (GridMap_ != nullptr)
    {
        grid = GridMap_[grid];
        if (grid >= 16) return;
    }

    if (SegMap_ != nullptr)
    {
        uint8_t actualSegs = 0;
        for (int i = 0; i < 8; ++i) if (segs & 1 << i) actualSegs |= 1 << SegMap_[i];
        segs = actualSegs;
    }

    Start();
    Write(0b11000000 | grid);   // Address command setting : Display address = grid
    Write(segs);                // Data
    End();
}
