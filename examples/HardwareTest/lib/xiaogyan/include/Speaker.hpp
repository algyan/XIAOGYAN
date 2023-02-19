/*
 * Speaker.hpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

#pragma once

#include <cstdbool>

class Speaker
{
private:
    int speakerPin_;
    int speakerEnablePin_;
    int ledControlChannel_;

public:
    Speaker(int speakerPin, int speakerEnablePin, int ledControlChannel);
    void begin();
    void setPowerSupply(bool on);
    void setTone(int frequency);

};
