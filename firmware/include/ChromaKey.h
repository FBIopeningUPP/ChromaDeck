#pragma once
#include <Arduino.h>

class ChromaKey {
private:
    uint8_t pin;
    uint8_t midiNote;

    bool isPressed;

    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 10;
public:
    ChromaKey(uint8_t hardwarePin, uint8_t note);
    void begin();
    bool update();
    uint8_t getNote();
    bool getState();
};