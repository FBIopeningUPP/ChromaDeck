#pragma once
#include <Arduino.h>

class ChromaFader {
private:
    uint8_t pin;
    uint8_t midiCC;

    int currentValue;
    float smoothedRaw;
    const float alpha = 0.15;
    const int threshold = 2;
public:
    ChromaFader(uint8_t hardwarePin, uint8_t ccNumber);
    void begin();
    bool update();
    uint8_t getCC();
    int getValue();
};