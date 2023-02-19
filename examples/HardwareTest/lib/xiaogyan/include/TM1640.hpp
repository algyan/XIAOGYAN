/*
 * TM1640.hpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

#pragma once

#include <cstdint>

class TM1640
{
private:
    int dinPin_;
    int sclkPin_;
    const uint8_t* gridMap_;
    const uint8_t* segMap_;

private:
    void init();
    void start();
    void write(uint8_t data);
    void end();

public:
    TM1640(int dinPin, int sclkPin);
    TM1640(int dinPin, int sclkPin, const uint8_t gridMap[16], const uint8_t segMap[8]);
    void begin();
    void setBrightness(int brightness);
    void setGrid(uint8_t grid, uint8_t segs);

};
