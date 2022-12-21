/*
 * main.cpp
 * Copyright (C) 2022 Takashi Matsuoka <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>
#include "Encoder.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants

static constexpr uint8_t ENCODER_A_PIN = D1;
static constexpr uint8_t ENCODER_B_PIN = D2;

////////////////////////////////////////////////////////////////////////////////
// setup and loop

static int EncoderCount_ = 0;
static Encoder Encoder_{
    ENCODER_A_PIN,
    ENCODER_B_PIN,
    [](bool cw){
        EncoderCount_ += cw ? 1 : -1;
        Serial.println(EncoderCount_);
    }
};

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    Encoder_.begin();
}

void loop()
{
    Encoder_.DoWork();
}

////////////////////////////////////////////////////////////////////////////////
