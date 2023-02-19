/*
 * Gpio.hpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <Arduino.h>

template <int PIN>
class GpioInputPin
{
public:
    static void begin(int mode)
    {
        if (mode != INPUT          &&
            mode != INPUT_PULLUP   &&
            mode != INPUT_PULLDOWN   ) abort();

        pinMode(PIN, mode);
    }

    static int read()
    {
        return digitalRead(PIN);
    }

};

template <int PIN>
class GpioOutputPin
{
public:
    static void begin()
    {
        pinMode(PIN, OUTPUT);
    }

    static void write(int value)
    {
        digitalWrite(PIN, value);
    }

};
