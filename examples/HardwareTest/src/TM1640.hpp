#pragma once

#include <cstdint>

class TM1640
{
private:
    int DinPin_;
    int SclkPin_;
    const uint8_t* GridMap_;
    const uint8_t* SegMap_;

private:
    void Init();
    void Start();
    void Write(uint8_t data);
    void End();

public:
    TM1640(int dinPin, int sclkPin);
    TM1640(int dinPin, int sclkPin, const uint8_t gridMap[16], const uint8_t segMap[8]);
    void begin();
    void SetBrightness(int brightness);
    void SetGrid(uint8_t grid, uint8_t segs);

};
