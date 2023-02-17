#include "Algyan8th.hpp"
#include <Arduino.h>

const uint8_t Algyan8thClass::TM1640_GRID_MAP[] =
{
    1,  3,  5,  6, 11, 12, 13, 14,
    0,  2,  4, 15, 10,  9,  8,  7,
};

const uint8_t Algyan8thClass::TM1640_ROW_MAP[] =
{
    6, 5, 7, 4, 0, 1, 2, 3,
};

TM1640 Algyan8thClass::tm1640_{ TM1640_DIN_PIN, TM1640_SCLK_PIN, TM1640_GRID_MAP, TM1640_ROW_MAP };
LedMatrix Algyan8thClass::ledMatrix_{ tm1640_ };

LedMatrixAGFX Algyan8thClass::ledMatrix{ ledMatrix_ };

Speaker Algyan8thClass::speaker{ SPEAKER_PIN, SPEAKER_ENABLE_PIN, SPEAKER_LEDC_CHANNEL };

Encoder Algyan8thClass::encoder{ ENCODER_A_PIN, ENCODER_B_PIN };

GpioOutputPin<Algyan8thClass::LED_PIN> Algyan8thClass::led;

void Algyan8thClass::begin()
{
    // Led Matrix
    Algyan8thClass::tm1640_.begin();
    Algyan8thClass::ledMatrix_.begin(true, LedMatrix::ScreenRotation::Degree270);

    // Speaker
    Algyan8thClass::speaker.begin();
    Algyan8thClass::speaker.setPowerSupply(true);

    // Encoder
    encoder.begin();

    // LED
    led.begin();

    // Buttons
    buttonA.begin(INPUT_PULLUP);
    buttonB.begin(INPUT_PULLUP);
}

void Algyan8thClass::doWork()
{
    encoder.doWork();
}

Algyan8thClass Algyan8th;
