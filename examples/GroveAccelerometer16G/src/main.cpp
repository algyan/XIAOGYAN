/*
 * main.cpp
 * Copyright (C) 2022 Takashi Matsuoka <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>
#include <Wire.h>

////////////////////////////////////////////////////////////////////////////////
// Constants

static constexpr uint8_t I2C_ADDRESS = 0x53;

static constexpr uint8_t REG_POWER_CTL  = 0x2d;
static constexpr uint8_t REG_DATAX0     = 0x32;

////////////////////////////////////////////////////////////////////////////////
// setup and loop

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    Wire.begin();
    Wire.setClock(400000);

    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(REG_POWER_CTL);
    Wire.write(0x08);
    if (Wire.endTransmission() != 0) abort();
}

void loop()
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(REG_DATAX0);
    if (Wire.endTransmission() != 0) abort();

    uint8_t readData[6];
    if (Wire.requestFrom(I2C_ADDRESS, sizeof(readData)) != sizeof(readData)) abort();
    for (size_t i = 0; i < sizeof(readData); ++i) readData[i] = Wire.read();

    int16_t val;

    ((uint8_t*)&val)[0] = readData[0];
    ((uint8_t*)&val)[1] = readData[1];
    float x = val * 2.0f / 512.0f;

    ((uint8_t*)&val)[0] = readData[2];
    ((uint8_t*)&val)[1] = readData[3];
    float y = val * 2.0f / 512.0f;

    ((uint8_t*)&val)[0] = readData[4];
    ((uint8_t*)&val)[1] = readData[5];
    float z = val * 2.0f / 512.0f;

    Serial.print(x);
    Serial.print(' ');
    Serial.print(y);
    Serial.print(' ');
    Serial.print(z);
    Serial.println();

    delay(200);
}

////////////////////////////////////////////////////////////////////////////////
