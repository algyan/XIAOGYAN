/*
 * TM1640.cpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include "TM1640.hpp"
#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
// TM1640

void TM1640::init()
{
    pinMode(dinPin_, OUTPUT);
    pinMode(sclkPin_, OUTPUT);
    digitalWrite(dinPin_, HIGH);
    digitalWrite(sclkPin_, HIGH);
    delayMicroseconds(1);
}

void TM1640::start()
{
    digitalWrite(dinPin_, LOW);
    delayMicroseconds(1);
}

void TM1640::write(uint8_t data)
{
    for (int i = 0; i < 8; ++i)
    {
        digitalWrite(sclkPin_, LOW);
        digitalWrite(dinPin_, data & 0x01 ? HIGH : LOW);
        digitalWrite(sclkPin_, HIGH);
        delayMicroseconds(1);

        data >>= 1;
    }
}

void TM1640::end()
{
    digitalWrite(sclkPin_, LOW);
    digitalWrite(dinPin_, LOW);
    digitalWrite(sclkPin_, HIGH);
    delayMicroseconds(1);
    digitalWrite(dinPin_, HIGH);
    delayMicroseconds(1);
}

TM1640::TM1640(int dinPin, int sclkPin) :
    dinPin_{ dinPin },
    sclkPin_{ sclkPin },
    gridMap_{ nullptr },
    segMap_{ nullptr }
{
}

TM1640::TM1640(int dinPin, int sclkPin, const uint8_t gridMap[16], const uint8_t segMap[8]) :
    dinPin_{ dinPin },
    sclkPin_{ sclkPin },
    gridMap_{ gridMap },
    segMap_{ segMap }
{
}

void TM1640::begin()
{
    init();

    start();
    write(0b01000000);  // Data command setting : Address auto + 1
    end();
}

void TM1640::setBrightness(int brightness)
{
    if (brightness < 0) brightness = 0;
    if (brightness > 8) brightness = 8;

    start();
    if (brightness == 0)
    {
        write(0b10000000);                  // Display control command setting : Display off
    }
    else
    {
        write(0b10001000 | brightness - 1); // Display control command setting : Set pulse width to 1/16-14/16
    }
    end();
}

void TM1640::setGrid(uint8_t grid, uint8_t segs)
{
    if (grid >= 16) return;

    if (gridMap_ != nullptr)
    {
        grid = gridMap_[grid];
        if (grid >= 16) return;
    }

    if (segMap_ != nullptr)
    {
        uint8_t actualSegs = 0;
        for (int i = 0; i < 8; ++i) if (segs & 1 << i) actualSegs |= 1 << segMap_[i];
        segs = actualSegs;
    }

    start();
    write(0b11000000 | grid);   // Address command setting : Display address = grid
    write(segs);                // Data
    end();
}

////////////////////////////////////////////////////////////////////////////////
