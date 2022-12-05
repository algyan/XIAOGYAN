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

static constexpr uint8_t TM1640_DIN_PIN = D10;
static constexpr uint8_t TM1640_SCLK_PIN = D8;

////////////////////////////////////////////////////////////////////////////////
// TM1640

class TM1640
{
private:
    uint8_t DinPin_;
    uint8_t SclkPin_;

private:
    void Init()
    {
        pinMode(DinPin_, OUTPUT);
        pinMode(SclkPin_, OUTPUT);
        digitalWrite(DinPin_, HIGH);
        digitalWrite(SclkPin_, HIGH);
        delayMicroseconds(1);
    }

    void Start()
    {
        digitalWrite(DinPin_, LOW);
        delayMicroseconds(1);
    }

    void Write(uint8_t data)
    {
        for (int i = 0; i < 8; ++i)
        {
            digitalWrite(SclkPin_, LOW);
            digitalWrite(DinPin_, data & 0x01 ? HIGH : LOW);
            digitalWrite(SclkPin_, HIGH);
            delayMicroseconds(1);

            data >>= 1;
        }
    }

    void End()
    {
        digitalWrite(SclkPin_, LOW);
        digitalWrite(DinPin_, LOW);
        digitalWrite(SclkPin_, HIGH);
        delayMicroseconds(1);
        digitalWrite(DinPin_, HIGH);
        delayMicroseconds(1);
    }

public:
    TM1640(uint8_t dinPin, uint8_t sclkPin) :
        DinPin_{ dinPin },
        SclkPin_{ sclkPin }
    {
    }

    void begin()
    {
        Init();

        Start();
        Write(0b01000000);  // Data command setting : Address auto + 1
        End();
    }

    void SetBrightness(uint8_t brightness)
    {
        if (brightness > 8) brightness = 8;

        Start();
        if (brightness == 0)
        {
            Write(0b10000000);                  // Display control command setting : Display off
        }
        else
        {
            Write(0b10001000 | brightness - 1); // Display control command setting : Set pulse width to 1/16-14/16
        }
        End();
    }

    void SetGrid(uint8_t grid, uint8_t dots)
    {
        if (grid >= 16) return;

        Start();
        Write(0b11000000 | grid);   // Address command setting : Display address = grid
        Write(dots);                // Data
        End();
    }

};

////////////////////////////////////////////////////////////////////////////////
// setup and loop

static TM1640 TM1640_{ TM1640_DIN_PIN, TM1640_SCLK_PIN };

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    TM1640_.begin();
    TM1640_.SetBrightness(2);
}

void loop()
{
    for (int i = 0; i < 8; ++i)
    {
        TM1640_.SetGrid(i, 0);
    }
    for (int i = 0; i < 8; ++i)
    {
        TM1640_.SetGrid(i, 0xff >> i);
        delay(100);
    }
    delay(2000);

    for (int i = 0; i < 8; ++i)
    {
        TM1640_.SetGrid(i, 0);
        delay(100);
    }
    delay(2000);
}

////////////////////////////////////////////////////////////////////////////////
