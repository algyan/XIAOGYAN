/*
 * main.cpp
 * Copyright (C) 2023 MATSUOKA Takashi <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////
// setup and loop

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    analogReadResolution(12);
}

void loop()
{
    const int value = analogRead(A3);
    Serial.println(value);

    delay(200);
}

////////////////////////////////////////////////////////////////////////////////
