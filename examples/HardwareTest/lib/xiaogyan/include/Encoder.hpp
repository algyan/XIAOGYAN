/*
 * Encoder.hpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

#pragma once

#include <cstdbool>
#include <cstdint>
#include <functional>

class Encoder
{
private:
    enum class EncoderDirection
    {
        Indefinite,
        Cw,
        Ccw,
    };

private:
    int aPin_;
    int bPin_;
    std::function<void(bool)> rotatedHandler_;

    EncoderDirection direction_;
    uint8_t value_;

public:
    Encoder(int aPin, int bPin);
    void begin();
    void setRotatedHandler(const std::function<void(bool)>& rotatedHandler);
    void doWork();

};
