#pragma once

#include <cstdint>
#include <functional>

class Encoder
{
private:
    enum class EncoderDirection
    {
        Indefinite,
        Cw,
        Ccw,
    };

private:
    int APin_;
    int BPin_;
    std::function<void(bool)> RotatedHandler_;

    EncoderDirection Direction_;
    uint8_t Value_;

public:
    Encoder(int aPin, int bPin, const std::function<void(bool)>& rotatedHandler);
    void begin();
    void DoWork();
    void SetRotatedHandler(const std::function<void(bool)>& rotatedHandler);

};
