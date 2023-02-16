/*
 * main.cpp
 * Copyright (C) 2023 MATSUOKA Takashi <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
// Constants

static constexpr uint8_t BUTTON_A_PIN = D9;
static constexpr uint8_t BUTTON_B_PIN = D7;
static constexpr uint8_t LED_PIN = D6;

////////////////////////////////////////////////////////////////////////////////
// setup and loop

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    Serial.print(digitalRead(BUTTON_A_PIN) == LOW ? '*' : '.');
    Serial.print(digitalRead(BUTTON_B_PIN) == LOW ? '*' : '.');
    Serial.println();

    digitalWrite(LED_PIN, digitalRead(BUTTON_A_PIN) == LOW || digitalRead(BUTTON_B_PIN) == LOW ? LOW : HIGH);

    delay(200);
}

////////////////////////////////////////////////////////////////////////////////
