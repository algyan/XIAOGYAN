/*
 * Encoder.cpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include "Encoder.hpp"
#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
// Encoder

Encoder::Encoder(int aPin, int bPin) :
    aPin_{ aPin },
    bPin_{ bPin },
    direction_{ EncoderDirection::Indefinite },
    value_{ 0b11 }
{
}

void Encoder::begin()
{
    pinMode(aPin_, INPUT_PULLUP);
    pinMode(bPin_, INPUT_PULLUP);
}

void Encoder::setRotatedHandler(const std::function<void(bool)>& rotatedHandler)
{
    rotatedHandler_ = rotatedHandler;
}

void Encoder::doWork()
{
    const uint8_t preValue = value_;
    value_ = 0;
    if (digitalRead(aPin_) == HIGH) value_ |= 0b01;
    if (digitalRead(bPin_) == HIGH) value_ |= 0b10;

    if (preValue == value_) return;

    if (direction_ == EncoderDirection::Indefinite)
    {
        switch (value_)
        {
        case 0b10:
            direction_ = EncoderDirection::Cw;
            break;
        case 0b01:
            direction_ = EncoderDirection::Ccw;
            break;
        }
    }
    else if (value_ == 0b11)
    {
        if (preValue == 0b01 && direction_ == EncoderDirection::Cw)
        {
            if (rotatedHandler_) rotatedHandler_(true);
        }
        else if (preValue == 0b10 && direction_ == EncoderDirection::Ccw)
        {
            if (rotatedHandler_) rotatedHandler_(false);
        }

        direction_ = EncoderDirection::Indefinite;
    }
}

////////////////////////////////////////////////////////////////////////////////
