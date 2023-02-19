/*
 * main.cpp
 * Copyright (C) 2023 MATSUOKA Takashi <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>
#include <elapsedMillis.h>
#include "Xiaogyan.hpp"

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

    Xiaogyan.begin();

    Xiaogyan.encoder.setRotatedHandler([](bool cw){
        const int value = EncoderValue_ + (cw ? -1 : 1);
        EncoderValue_ = constrain(value, 0, 19);
        Serial.println(EncoderValue_);
    });

    ////////////////////////////////////////
    // Startup Sequence

    Xiaogyan.speaker.setTone(262);  // C4
    Xiaogyan.ledMatrix.setBrightness(2);
    Xiaogyan.ledMatrix.fillScreen(1);
    delay(200);

    Xiaogyan.speaker.setTone(0);
    Xiaogyan.ledMatrix.fillScreen(0);
}

void loop()
{
    // Xiaogyan
    Xiaogyan.doWork();

    // LED
    Xiaogyan.led.write(millis() % 1000 < 200 ? LOW : HIGH);

    // Buttons
    static bool buttonA = false;
    static bool buttonB = false;
    bool preButtonA = buttonA;
    bool preButtonB = buttonB;
    buttonA = Xiaogyan.buttonA.read() == LOW;
    buttonB = Xiaogyan.buttonB.read() == LOW;
    if (preButtonA != buttonA || preButtonB != buttonB)
    {
        if      ( buttonA && !buttonB) Xiaogyan.speaker.setTone(262);   // C4
        else if (!buttonA &&  buttonB) Xiaogyan.speaker.setTone(294);   // D4
        else if ( buttonA &&  buttonB) Xiaogyan.speaker.setTone(330);   // E4
        else                           Xiaogyan.speaker.setTone(0);
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

        Xiaogyan.ledMatrix.drawPixel(x, y, COLOR_MAP[colorIndex]);

        if (++x >= Xiaogyan.ledMatrix.width())
        {
            x = 0;
            if (++colorIndex >= std::extent<decltype(COLOR_MAP)>::value)
            {
                colorIndex = 0;
                if (++y >= Xiaogyan.ledMatrix.height())
                {
                    y = 0;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
