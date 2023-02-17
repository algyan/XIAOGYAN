/*
 * main.cpp
 * Copyright (C) 2023 MATSUOKA Takashi <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>
#include <elapsedMillis.h>
#include "Algyan8th.hpp"

////////////////////////////////////////////////////////////////////////////////
// Variables

static int EncoderValue_ = 5;

////////////////////////////////////////////////////////////////////////////////
// setup and loop

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println();

    ////////////////////////////////////////
    // Initialize

    Algyan8th.begin();

    Algyan8th.encoder.setRotatedHandler([](bool cw){
        const int value = EncoderValue_ + (cw ? -1 : 1);
        EncoderValue_ = constrain(value, 0, 19);
        Serial.println(EncoderValue_);
    });

    ////////////////////////////////////////
    // Startup Sequence

    Algyan8th.speaker.setTone(262); // C4
    Algyan8th.ledMatrix.setBrightness(2);
    Algyan8th.ledMatrix.fillScreen(1);
    delay(200);

    Algyan8th.speaker.setTone(0);
    Algyan8th.ledMatrix.fillScreen(0);
}

void loop()
{
    // Algyan8th
    Algyan8th.doWork();

    // LED
    Algyan8th.led.write(millis() % 1000 < 200 ? LOW : HIGH);

    // Buttons
    static bool buttonA = false;
    static bool buttonB = false;
    bool preButtonA = buttonA;
    bool preButtonB = buttonB;
    buttonA = Algyan8th.buttonA.read() == LOW;
    buttonB = Algyan8th.buttonB.read() == LOW;
    if (preButtonA != buttonA || preButtonB != buttonB)
    {
        if      ( buttonA && !buttonB) Algyan8th.speaker.setTone(262);  // C4
        else if (!buttonA &&  buttonB) Algyan8th.speaker.setTone(294);  // D4
        else if ( buttonA &&  buttonB) Algyan8th.speaker.setTone(330);  // E4
        else                           Algyan8th.speaker.setTone(0);
    }

    // Led Matrix
    static const int COLOR_MAP[] = { 1, 0, 2, 0, 3, 0, };
    static int x = 0;
    static int y = 0;
    static int colorIndex = 0;
    static elapsedMillis ledMatrixElapsed{ 0 };

    if (ledMatrixElapsed >= (EncoderValue_ + 1) * 10)
    {
        ledMatrixElapsed = 0;

        Algyan8th.ledMatrix.drawPixel(x, y, COLOR_MAP[colorIndex]);

        if (++x >= Algyan8th.ledMatrix.width())
        {
            x = 0;
            if (++colorIndex >= std::extent<decltype(COLOR_MAP)>::value)
            {
                colorIndex = 0;
                if (++y >= Algyan8th.ledMatrix.height())
                {
                    y = 0;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
