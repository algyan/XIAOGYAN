#pragma once

#include <cstdint>

class TM1640
{
private:
    int DinPin_;
    int SclkPin_;

private:
    void Init();
    void Start();
    void Write(uint8_t data);
    void End();

public:
    TM1640(int dinPin, int sclkPin);
    void begin();
    void SetBrightness(int brightness);
    void SetGrid(uint8_t grid, uint8_t dots);

};
