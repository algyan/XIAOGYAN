#pragma once

#include <cstdbool>

class Speaker
{
private:
    int SpeakerPin_;
    int SpeakerEnablePin_;
    int LedControlChannel_;

public:
    Speaker(int speakerPin, int speakerEnablePin, int ledControlChannel);
    void begin();
    void PowerSupply(bool on);
    void Tone(int frequency);

};
