/*
 * main.cpp
 * Copyright (C) 2022 Takashi Matsuoka <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
// Constants

static constexpr uint8_t SELECT_BUTTON_PIN = D7;
static constexpr uint8_t ESCAPE_BUTTON_PIN = D9;
static constexpr uint8_t LED_PIN = D6;

////////////////////////////////////////////////////////////////////////////////
// setup and loop

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(ESCAPE_BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    Serial.print(digitalRead(SELECT_BUTTON_PIN) == LOW ? '*' : '.');
    Serial.print(digitalRead(ESCAPE_BUTTON_PIN) == LOW ? '*' : '.');
    Serial.println();

    digitalWrite(LED_PIN, digitalRead(SELECT_BUTTON_PIN) == LOW || digitalRead(ESCAPE_BUTTON_PIN) == LOW ? LOW : HIGH);

    delay(200);
}

////////////////////////////////////////////////////////////////////////////////
