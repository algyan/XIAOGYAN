/*
 * main.cpp
 * Copyright (C) 2023 MATSUOKA Takashi <matsujirushi@live.jp>
 * MIT License
 */

////////////////////////////////////////////////////////////////////////////////
// Includes

#include <Arduino.h>
#include <elapsedMillis.h>
#include "TM1640.hpp"
#include "LedMatrix.hpp"
#include "LedMatrixAGFX.hpp"
#include "Speaker.hpp"
#include "Encoder.hpp"

////////////////////////////////////////////////////////////////////////////////
// Constants

static constexpr uint8_t TM1640_DIN_PIN     = D10;
static constexpr uint8_t TM1640_SCLK_PIN    = D8;
static constexpr uint8_t SPEAKER_PIN        = D0;
static constexpr uint8_t SPEAKER_ENABLE_PIN = D3;
static constexpr uint8_t ENCODER_A_PIN      = D1;
static constexpr uint8_t ENCODER_B_PIN      = D2;
static constexpr uint8_t LED_PIN            = D6;
static constexpr uint8_t BUTTON_A_PIN       = D9;
static constexpr uint8_t BUTTON_B_PIN       = D7;

static constexpr uint8_t SPEAKER_LEDC_CHANNEL = 0;

static const uint8_t TM1640_GRID_MAP[] =
{
    1,  3,  5,  6, 11, 12, 13, 14,
    0,  2,  4, 15, 10,  9,  8,  7,
};

static const uint8_t TM1640_ROW_MAP[] =
{
    6, 5, 7, 4, 0, 1, 2, 3,
};

////////////////////////////////////////////////////////////////////////////////
// Variables

static TM1640 TM1640_{ TM1640_DIN_PIN, TM1640_SCLK_PIN, TM1640_GRID_MAP, TM1640_ROW_MAP };
static LedMatrix LedMatrix_{ TM1640_ };
static LedMatrixAGFX LedMatrixAGFX_{ LedMatrix_ };

static Speaker Speaker_{ SPEAKER_PIN, SPEAKER_ENABLE_PIN, SPEAKER_LEDC_CHANNEL };

static int EncoderValue_ = 5;
static Encoder Encoder_{
    ENCODER_A_PIN,
    ENCODER_B_PIN,
    [](bool cw){
        const int value = EncoderValue_ + (cw ? -1 : 1);
        EncoderValue_ = constrain(value, 0, 19);
        Serial.println(EncoderValue_);
    }
};

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

    // Led Matrix
    TM1640_.begin();
    LedMatrix_.begin(true, LedMatrix::ScreenRotation::Degree270);

    // Speaker
    Speaker_.begin();
    Speaker_.PowerSupply(true);

    // Encoder
    Encoder_.begin();

    // LED
    pinMode(BUTTON_A_PIN, INPUT_PULLUP);
    pinMode(BUTTON_B_PIN, INPUT_PULLUP);

    // Buttons
    pinMode(LED_PIN, OUTPUT);

    ////////////////////////////////////////
    // Startup Sequence

    Speaker_.Tone(262); // C4
    TM1640_.SetBrightness(2);
    LedMatrixAGFX_.fillScreen(1);
    delay(200);

    Speaker_.Tone(0);
    LedMatrixAGFX_.fillScreen(0);
}

void loop()
{
    // LED
    digitalWrite(LED_PIN, millis() % 1000 < 200 ? LOW : HIGH);

    // Buttons
    static bool buttonA = false;
    static bool buttonB = false;
    bool preButtonA = buttonA;
    bool preButtonB = buttonB;
    buttonA = digitalRead(BUTTON_A_PIN) == LOW;
    buttonB = digitalRead(BUTTON_B_PIN) == LOW;
    if (preButtonA != buttonA || preButtonB != buttonB)
    {
        if      ( buttonA && !buttonB) Speaker_.Tone(262);  // C4
        else if (!buttonA &&  buttonB) Speaker_.Tone(294);  // D4
        else if ( buttonA &&  buttonB) Speaker_.Tone(330);  // E4
        else                           Speaker_.Tone(0);
    }

    // Encoder
    Encoder_.DoWork();

    // Led Matrix
    static const int COLOR_MAP[] = { 1, 0, 2, 0, 3, 0, };
    static int x = 0;
    static int y = 0;
    static int colorIndex = 0;
    static elapsedMillis ledMatrixElapsed{ 0 };

    if (ledMatrixElapsed >= (EncoderValue_ + 1) * 10)
    {
        ledMatrixElapsed = 0;

        LedMatrixAGFX_.drawPixel(x, y, COLOR_MAP[colorIndex]);

        if (++x >= LedMatrixAGFX_.width())
        {
            x = 0;
            if (++colorIndex >= std::extent<decltype(COLOR_MAP)>::value)
            {
                colorIndex = 0;
                if (++y >= LedMatrixAGFX_.height())
                {
                    y = 0;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
