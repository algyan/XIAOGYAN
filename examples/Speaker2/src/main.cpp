/*
 * main.cpp
 * Copyright (C) 2022 Takashi Matsuoka <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>
#include "Speaker.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants

static constexpr uint8_t SPEAKER_PIN = D0;
static constexpr uint8_t SPEAKER_ENABLE_PIN = D3;
static constexpr uint8_t SPEAKER_LEDC_CHANNEL = 0;

////////////////////////////////////////////////////////////////////////////////
// setup and loop

static Speaker Speaker_{ SPEAKER_PIN, SPEAKER_ENABLE_PIN, SPEAKER_LEDC_CHANNEL };

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    Speaker_.begin();
    Speaker_.PowerSupply(true);
}

void loop()
{
    Speaker_.Tone(262); // C4
    delay(500);
    Speaker_.Tone(294); // D4
    delay(500);
    Speaker_.Tone(330); // E4
    delay(500);
    Speaker_.Tone(349); // F4
    delay(500);
    Speaker_.Tone(392); // G4
    delay(500);
    Speaker_.Tone(440); // A4
    delay(500);
    Speaker_.Tone(494); // B4
    delay(500);
    Speaker_.Tone(523); // C5
    delay(500);

    Speaker_.Tone(0);
    delay(1000);
}

////////////////////////////////////////////////////////////////////////////////
