/*
 * Speaker.cpp
 * Copyright (C) 2023 MATSUOKA Takashi
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include "Speaker.hpp"
#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
// Speaker

Speaker::Speaker(int speakerPin, int speakerEnablePin, int ledControlChannel) :
    speakerPin_{ speakerPin },
    speakerEnablePin_{ speakerEnablePin },
    ledControlChannel_{ ledControlChannel }
{
}

void Speaker::begin()
{
    pinMode(speakerEnablePin_, OUTPUT);
    digitalWrite(speakerEnablePin_, HIGH);
    ledcAttachPin(speakerPin_, ledControlChannel_);
}

void Speaker::setPowerSupply(bool on)
{
    digitalWrite(speakerEnablePin_, on ? LOW : HIGH);
}

void Speaker::setTone(int frequency)
{
    ledcWriteTone(ledControlChannel_, frequency);
}

////////////////////////////////////////////////////////////////////////////////
