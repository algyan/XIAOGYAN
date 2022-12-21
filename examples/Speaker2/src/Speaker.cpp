#include "Speaker.hpp"
#include <Arduino.h>

Speaker::Speaker(int speakerPin, int speakerEnablePin, int ledControlChannel) :
    SpeakerPin_{ speakerPin },
    SpeakerEnablePin_{ speakerEnablePin },
    LedControlChannel_{ ledControlChannel }
{
}

void Speaker::begin()
{
    pinMode(SpeakerEnablePin_, OUTPUT);
    digitalWrite(SpeakerEnablePin_, HIGH);
    ledcAttachPin(SpeakerPin_, LedControlChannel_);
}

void Speaker::PowerSupply(bool on)
{
    digitalWrite(SpeakerEnablePin_, on ? LOW : HIGH);
}

void Speaker::Tone(int frequency)
{
    ledcWriteTone(LedControlChannel_, frequency);
}
