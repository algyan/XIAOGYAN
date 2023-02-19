#include "Xiaogyan.hpp"
#include <Arduino.h>

const uint8_t XiaogyanClass::TM1640_GRID_MAP[] =
{
    1,  3,  5,  6, 11, 12, 13, 14,
    0,  2,  4, 15, 10,  9,  8,  7,
};

const uint8_t XiaogyanClass::TM1640_ROW_MAP[] =
{
    6, 5, 7, 4, 0, 1, 2, 3,
};

TM1640 XiaogyanClass::tm1640_{ TM1640_DIN_PIN, TM1640_SCLK_PIN, TM1640_GRID_MAP, TM1640_ROW_MAP };
LedMatrix XiaogyanClass::ledMatrix_{ tm1640_ };

LedMatrixAGFX XiaogyanClass::ledMatrix{ ledMatrix_ };

Speaker XiaogyanClass::speaker{ SPEAKER_PIN, SPEAKER_ENABLE_PIN, SPEAKER_LEDC_CHANNEL };

Encoder XiaogyanClass::encoder{ ENCODER_A_PIN, ENCODER_B_PIN };

GpioOutputPin<XiaogyanClass::LED_PIN> XiaogyanClass::led;

void XiaogyanClass::begin()
{
    // Led Matrix
    XiaogyanClass::tm1640_.begin();
    XiaogyanClass::ledMatrix_.begin(true, LedMatrix::ScreenRotation::Degree270);

    // Speaker
    XiaogyanClass::speaker.begin();
    XiaogyanClass::speaker.setPowerSupply(true);

    // Encoder
    encoder.begin();

    // LED
    led.begin();

    // Buttons
    buttonA.begin(INPUT_PULLUP);
    buttonB.begin(INPUT_PULLUP);
}

void XiaogyanClass::doWork()
{
    encoder.doWork();
}

XiaogyanClass Xiaogyan;
