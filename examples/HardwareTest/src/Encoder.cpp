#include "Encoder.hpp"
#include <Arduino.h>

Encoder::Encoder(int aPin, int bPin, const std::function<void(bool)>& rotatedHandler) :
    APin_{ aPin },
    BPin_{ bPin },
    RotatedHandler_{ rotatedHandler },
    Direction_{ EncoderDirection::Indefinite },
    Value_{ 0b11 }
{
}

void Encoder::begin()
{
    pinMode(APin_, INPUT_PULLUP);
    pinMode(BPin_, INPUT_PULLUP);
}

void Encoder::DoWork()
{
    const uint8_t preValue = Value_;
    Value_ = 0;
    if (digitalRead(APin_) == HIGH) Value_ |= 0b01;
    if (digitalRead(BPin_) == HIGH) Value_ |= 0b10;

    if (preValue == Value_) return;

    if (Direction_ == EncoderDirection::Indefinite)
    {
        switch (Value_)
        {
        case 0b10:
            Direction_ = EncoderDirection::Cw;
            break;
        case 0b01:
            Direction_ = EncoderDirection::Ccw;
            break;
        }
    }
    else if (Value_ == 0b11)
    {
        if (preValue == 0b01 && Direction_ == EncoderDirection::Cw)
        {
            if (RotatedHandler_) RotatedHandler_(true);
        }
        else if (preValue == 0b10 && Direction_ == EncoderDirection::Ccw)
        {
            if (RotatedHandler_) RotatedHandler_(false);
        }

        Direction_ = EncoderDirection::Indefinite;
    }
}

void Encoder::SetRotatedHandler(const std::function<void(bool)>& rotatedHandler)
{
    RotatedHandler_ = rotatedHandler;
}
